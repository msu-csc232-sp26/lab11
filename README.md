# LHWn - Title

[//]: # (Make sure you update the following URL with the correct repo name)
[![Autograding](https://github.com/msu-csc232-sp26/google-test-template/actions/workflows/autograding.yml/badge.svg?branch=develop)](https://github.com/msu-csc232-sp26/google-test-template/actions/workflows/autograding.yml)

_A quick blurb or sub-title text_

## Background

Before proceeding with this lab, the student should take the time to read

* this
* that
* and the other thing

## Objective

Upon successful completion of this lab, the student has learned how to

* do this
* do that
* do another thing

## Getting Started

After accepting this assignment with the provided GitHub Classroom Assignment link, decide how you want to work with
your newly created repository:

* Using Codespaces directly in your web browser that employees the Visual Studio Code online IDE, or
* Using the IDE of your choice on your local machine

See [setup](setup.md) for more details around setting up your development environment once you've cloned your
assignment.

## Tasks

This assignment consists of the following tasks:

* Task 1: <TODO: Declare me!>
* Task 2: <TODO: Declare me!>
* Task 3: <TODO: Declare me!>
* Task 4: <TODO: Declare me - or erase me!>
* Task 5: <TODO: Declare me - or erase me!>

Pol, neuter abactor!

### Task 1: <TODO: Declare me!>

Enumerated below are the essential steps to completing this task. For a deeper dive before you begin, see
the [Task 1 Details](task1.md) document.

### Task 2: <TODO: Declare me!>

Enumerated below are the essential steps to completing this task. For a deeper dive before you begin, see
the [Task 2 Details](task2.md) document.

### Task 3: <TODO: Declare me!>

Enumerated below are the essential steps to completing this task. For a deeper dive before you begin, see
the [Task 3 Details](task3.md) document.

### Task 4: <TODO: Declare me!>

Enumerated below are the essential steps to completing this task. For a deeper dive before you begin, see
the [Task 4 Details](task4.md) document.

### Task 5: <TODO: Declare me!>

Enumerated below are the essential steps to completing this task. For a deeper dive before you begin, see
the [Task 5 Details](task5.md) document.

## Submission Details

Before submitting your assignment, be sure you have pushed all your changes to GitHub. If this is the first time you're
pushing your changes, the push command will look like:

```bash
git push -u origin develop
```

If you've already set up remote tracking (using the `-u origin develop` switch), then all you need to do is type

```bash
git push
```

As usual, prior to submitting your assignment on Brightspace, be sure that you have committed and pushed your final
changes to GitHub. Once your final changes have been pushed, create a pull request that seeks to merge the changes in
your `develop` branch into your `main` branch.

You can use `gh` to create this pull request right from your command-line prompt:

```bash
gh pr create --assignee "@me" --title "Some appropriate title" --body "A message to populate description, e.g., Go Bills!" --head develop --base main --reviewer msu-csc232-fa25/graders
```

An "appropriate" title is at a minimum, the name of the assignment, e.g., `LAB02` or `HW04`, etc.

Once your pull request has been created, submit the URL of your assignment _repository_ (i.e., _not_ the URL of the pull
request) as a Text Submission on Brightspace. Please note: the timestamp of the submission on Brightspace is used to
assess any late penalties if and when warranted, _not_ the date/time you create your pull request. **No exceptions will
be granted for this oversight**.

### Due Date

Your assignment submission is due by ...

### Grading Rubric

This assignment is worth **3|5 points**.

| Criteria           | Exceeds Expectations         | Meets Expectations                  | Below Expectations                  | Failure                                        |
|--------------------|------------------------------|-------------------------------------|-------------------------------------|------------------------------------------------|
| Pull Request (20%) | Submitted early, correct url | Submitted on-time; correct url      | Incorrect URL                       | No pull request was created or submitted       |
| Code Style (20%)   | Exemplary code style         | Consistent, modern coding style     | Inconsistent coding style           | No style whatsoever or no code changes present |
| Correctness^ (60%) | All unit tests pass          | At least 80% of the unit tests pass | At least 60% of the unit tests pass | Less than 50% of the unit tests pass           |

^ _The Google Test unit runner will calculate the correctness points based purely on the fraction of tests passed_.

### Late Penalty

* In the first 24-hour period following the due date, this assignment will be penalized 20%.
* In the second 24-hour period following the due date, this assignment will be penalized 40%.
* After 48 hours, the assignment will not be graded and thus earns no points.

## Disclaimer & Fair Use Statement

This repository may contain copyrighted material, the use of which may not
have been specifically authorized by the copyright owner. This material is
available in an effort to explain issues relevant to the course or to
illustrate the use and benefits of an educational tool. The material
contained in this repository is distributed without profit for research and
educational purposes. Only small portions of the original work are being
used and those could not be used to easily duplicate the original work.
