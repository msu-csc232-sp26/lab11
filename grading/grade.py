#!/usr/bin/env python3

import datetime
import json
import os
import sys
from pathlib import Path
from xml.etree import ElementTree


# ============================================================
# Helpers
# ============================================================

def parse_iso_utc(ts: str) -> datetime.datetime:
    """
    Parse an ISO-8601 timestamp (with or without timezone) into UTC.
    Accepts strings like:
      - 2026-03-28T21:22:30Z
      - 2026-04-01T23:59:00
    """
    dt = datetime.datetime.fromisoformat(ts.replace("Z", "+00:00"))
    if dt.tzinfo is None:
        dt = dt.replace(tzinfo=datetime.timezone.utc)
    return dt


def score_fraction(fraction: float) -> float:
    """
    Map fraction of passing tests to score multiplier.

    Policy:
      100% pass        -> 1.00
      [75%, <100%)    -> 0.80
      [50%, <75%)     -> 0.60
      <50%            -> 0.00
    """
    if fraction == 1.0:
        return 1.0
    if fraction >= 0.75:
        return 0.8
    if fraction >= 0.5:
        return 0.6
    return 0.0


def parse_junit_counts(xml_path: Path) -> tuple[int, int]:
    """
    Count passed and total tests from a JUnit XML file.
    Returns: (passed, total)
    """
    tree = ElementTree.parse(xml_path)
    root = tree.getroot()

    total = 0
    failed = 0

    for case in root.iter("testcase"):
        total += 1
        if case.find("failure") is not None or case.find("error") is not None:
            failed += 1

    return total - failed, total


# ============================================================
# Load rubric
# ============================================================

RUBRIC_PATH = Path("grading/rubric.json")
if not RUBRIC_PATH.exists():
    print("ERROR: grading/rubric.json not found")
    sys.exit(1)

with RUBRIC_PATH.open() as f:
    rubric = json.load(f)

total_points = rubric["total_points"]
raw_score = 0.0
breakdown: dict[str, int] = {}

# IMPORTANT:
# CI + Classroom workflows write JUnit XML files here:
results_dir = Path(
    os.getenv("TEST_RESULTS_DIR", "results")
).resolve()

if not results_dir.exists():
    print(f"[ERROR] Results directory not found: {results_dir}")
    sys.exit(1)

# ============================================================
# Task grading (preset-scoped, partial credit)
# ============================================================

# Expected rubric format:
# {
#   "tasks": {
#     "task1": { "name": "...", "points": 10 },
#     "task1-2": { "name": "...", "points": 15 },
#     ...
#   }
# }

for preset, task in rubric["tasks"].items():
    xml_file = results_dir / f"{preset}.xml"
    label = f"{preset} ({task['name']})"

    if not xml_file.exists():
        breakdown[label] = 0
        continue

    passed, total = parse_junit_counts(xml_file)

    if total == 0:
        breakdown[label] = 0
        continue

    fraction = passed / total
    multiplier = score_fraction(fraction)

    task_points = round(task["points"] * multiplier)
    raw_score += task_points
    breakdown[label] = task_points

# ============================================================
# Lint scoring
# ============================================================

lint_cfg = rubric.get("lint", {})
lint_points = lint_cfg.get("points", 0)
penalty_per_issue = lint_cfg.get("penalty_per_issue", 0)
max_penalty = lint_cfg.get("max_penalty", lint_points)

lint_issues = int(os.getenv("LINT_ISSUES", "0"))
lint_penalty = min(lint_issues * penalty_per_issue, max_penalty)

lint_score = max(lint_points - lint_penalty, 0)
raw_score += lint_score
breakdown["Lint"] = lint_score

# ============================================================
# Late policy (piecewise + hard-zero override)
# ============================================================

late_percent = 0
hard_zero = False

due_str = os.getenv("DUE_AT")
submitted_str = os.getenv("SUBMITTED_AT")

if due_str and submitted_str:
    due_dt = parse_iso_utc(due_str)
    sub_dt = parse_iso_utc(submitted_str)

    delta = sub_dt - due_dt
    hours_late = delta.total_seconds() / 3600

    if hours_late > 48:
        hard_zero = True
    elif hours_late > 24:
        late_percent = 40
    elif hours_late > 0:
        late_percent = 20

# ============================================================
# Final score computation
# ============================================================

if hard_zero:
    final_score = 0
else:
    penalty_points = int(raw_score * late_percent / 100)
    final_score = max(int(raw_score - penalty_points), 0)

# ============================================================
# Persist machine-readable result
# ============================================================

Path("grading").mkdir(exist_ok=True)

result = {
    "assignment": rubric["assignment"],
    "raw_score": int(raw_score),
    "late_penalty_percent": late_percent,
    "hard_zero": hard_zero,
    "final_score": final_score,
    "total": total_points,
    "breakdown": breakdown,
}

with open("grading/result.json", "w") as f:
    json.dump(result, f, indent=2)

# ============================================================
# Workflow Summary (human-readable for GitHub Actions)
# ============================================================

summary_path = os.getenv("GITHUB_STEP_SUMMARY")
if summary_path:
    with open(summary_path, "a") as f:
        f.write("## Autograding Report\n\n")
        f.write("| Item | Points |\n")
        f.write("|------|--------|\n")

        for k, v in breakdown.items():
            f.write(f"| {k} | {v} |\n")

        f.write(f"\nRaw score: **{int(raw_score)} / {total_points}**\n")
        f.write(f"Late penalty: **{late_percent}%**\n")

        if hard_zero:
            f.write(
                "\n### Late Submission\n"
                "Submission was more than **48 hours late**. "
                "Score set to **0** by policy.\n"
            )
        else:
            f.write(f"\n### Final Score: **{final_score} / {total_points}**\n")

# ============================================================
# Console output (logs / Classroom)
# ============================================================

print("=== AUTOGRADING RESULT ===")
for k, v in breakdown.items():
    print(f"{k}: {v}")

if hard_zero:
    print("Late submission >48 hours: score set to 0 by policy.")
else:
    print(f"Late penalty: {late_percent}%")

print(f"FINAL SCORE: {final_score}/{total_points}")

# GitHub Classroom expects exit code 0 for a valid grading run
sys.exit(0)
