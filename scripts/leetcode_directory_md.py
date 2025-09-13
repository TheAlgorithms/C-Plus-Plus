#!/usr/bin/env python3

from dataclasses import dataclass
from os import listdir
from pathlib import Path

import requests


@dataclass
class Task:
    """The task dataclass. Container for task info"""

    id: str
    title: str
    solution: str
    difficulty: str


def fetch_leetcode_folder_tasks(solutions_folder: Path) -> list[Task]:
    """Fetch leetcode tasks from the Leetcode"""

    # Fetch tasks info from the leetcode API.
    resp = requests.get("https://leetcode.com/api/problems/algorithms/", timeout=10)
    content_dict = resp.json()

    raw_tasks_id_dict = {}

    for task in content_dict["stat_status_pairs"]:
        task_stat = task["stat"]
        raw_tasks_id_dict[str(task_stat["frontend_question_id"])] = task

    # Generate result tasks info to be inserted into the document
    tasks_list = []

    difficulty = {1: "Easy", 2: "Medium", 3: "Hard"}

    for fl in listdir(solutions_folder):
        task_id = fl.split(".")[0]

        raw_task = raw_tasks_id_dict.get(task_id, None)
        if raw_task is None:
            continue

        raw_task_stat = raw_task["stat"]
        tasks_list.append(
            Task(
                id=f'{raw_task_stat["frontend_question_id"]}',
                title=f'[{raw_task_stat["question__title"]}](https://leetcode.com/problems/{raw_task_stat["question__title_slug"]})',
                solution=f"[C++](./src/{fl})",
                difficulty=f'{difficulty.get(raw_task["difficulty"]["level"], "")}',
            )
        )

    return tasks_list


HEADER_ID = "#"
HEADER_TITLE = "Title"
HEADER_SOLUTION = "Solution"
HEADER_DIFFICULTY = "Difficulty"
SEPARATOR = "-"


def print_directory_md(tasks_list: list[Task]) -> None:
    """Print tasks into the stdout"""

    def get_max_len(get_item):
        return max(list(map(lambda x: len(get_item(x)), tasks_list)))

    id_max_length = max(get_max_len(lambda x: x.id), len(HEADER_ID))
    title_max_length = max(get_max_len(lambda x: x.title), len(HEADER_TITLE))
    solution_max_length = max(get_max_len(lambda x: x.solution), len(HEADER_SOLUTION))
    difficulty_max_length = max(
        get_max_len(lambda x: x.difficulty), len(HEADER_DIFFICULTY)
    )

    def formatted_string(header, title, solution, difficulty):
        return (
            f"| {header.rjust(id_max_length)} "
            + f"| {title.ljust(title_max_length)} "
            + f"| {solution.ljust(solution_max_length)} "
            + f"| {difficulty.ljust(difficulty_max_length)} |"
        )

    tasks_rows = []

    tasks_rows.append(
        formatted_string(HEADER_ID, HEADER_TITLE, HEADER_SOLUTION, HEADER_DIFFICULTY)
    )
    tasks_rows.append(
        formatted_string(
            id_max_length * SEPARATOR,
            title_max_length * SEPARATOR,
            solution_max_length * SEPARATOR,
            difficulty_max_length * SEPARATOR,
        )
    )

    tasks_list.sort(key=lambda x: int(x.id.strip()))

    for task in tasks_list:
        tasks_rows.append(
            formatted_string(task.id, task.title, task.solution, task.difficulty)
        )

    print(
        """
# LeetCode

### LeetCode Algorithm
"""
    )

    for item in tasks_rows:
        print(item)


if __name__ == "__main__":
    top_dir = Path(".")
    solutions_folder = top_dir / "leetcode" / "src"

    tasks_list = fetch_leetcode_folder_tasks(solutions_folder)
    print_directory_md(tasks_list)
