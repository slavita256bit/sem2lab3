---
name: slavita-cpp-style
description: "Plan, implement, refactor, and review Slavita's C/C++ coursework in his preferred concise style and his teacher's conventions. Use for lab code, containers, class hierarchies, console menus, and requests to match his code style; not for unrelated projects or report writing."
---

# Slavita's C/C++ Style

Write straightforward coursework code the student can understand and explain to the
teacher. This skill reflects agreed decisions from string, inheritance, and template
tree labs; those assignments' domain details are not requirements for every program.

## Establish the active constraints first

Read the current AGENTS.md section, STYLE.md, assignment, and affected source files.
Distinguish active rules from preserved history, and proposals for the next lab from
approved implementation. The user's latest explicit instructions override this skill.
Reread affected code before editing: the user may be changing it concurrently.
Preserve their edits; do not reformat a whole project for a small change.

Before writing or reviewing code, read [references/codestyle.md](references/codestyle.md).
For component selection and refactoring, also read
[references/design-review.md](references/design-review.md).

Never create commits or deploy. Do not delete or move files without explicit
permission. Verify the execution environment and give commands an explicit working
directory.

## 1. Plan the implementation and choose components

For a substantive task, briefly establish:

- The requested behavior and what the student must demonstrate at the lab defense.
- Existing classes and files that already solve part of the problem.
- What the standard library can provide and what the assignment requires implementing.
- Where data lives, who owns and releases it, and where state changes.
- Which declarations belong in h, which definitions in cpp/tpp, and which files are needed.
- Scenarios that will verify the outcome, proportional to the change's risk.

Design for the current assignment rather than hypothetical future labs. A local edit
needs only a few sentences, not a large plan.md. Write a plan file when requested or
when the project maintains one. If the user has left a structural choice open,
ask before replacing functions with a class, changing who owns the menu flow,
or splitting a handler into several methods. Briefly present the options and
your recommendation. Continue independent work while waiting for that choice.
An explicit request for the structure already answers the question. Routine
local fixes do not need confirmation.

## 2. Reassess the design before implementation

Review each proposed class, file, and wrapper a second time: what present problem
does it solve, and could more direct code solve that problem?

- Compare a nontrivial choice with at least one simpler alternative.
- Do not hide several actions behind interaction/demonstration/Application or a factory
  just to shorten main. Simplify the sequence of actions itself.
- Do not replace a short switch with an extra hierarchy, type erasure, or metaprogramming.
- Consolidate actual repetition, but do not introduce a mechanism more complex than it.
- Check static types, operator overload selection, ownership, container ordering, and
  reference/generator lifetime. Do not promise that a cast solves an interface mismatch.
- Assess the cost of a ready-made std facility: assignment compliance, compiler support,
  explainability, and API constraints. Justify a language-standard upgrade before using it.

Briefly communicate significant design changes, then continue the authorized work.

## 3. Implement in the agreed style

Follow references/codestyle.md while preserving the project's latest local refinements.
Implement the smallest working solution first. Do not bundle unrelated refactors,
menus, file operations, or next-lab validation into the requested change.

Prefer std where it does not replace the learning objective. Do not substitute a
standard string/container for the custom String/tree the assignment requires.
Do not introduce smart pointers, variant, or extra templates against the user's
explicit choice. Lab-specific restrictions are not universal bans on language features.

While the active project prohibits exceptions and stream-state checks, do not add
them as unsolicited hardening. An error-handling assignment changes that scope:
EOF handling, retrying recoverable input, and preserving objects become necessary.
Do not confuse index/menu/bounds validation with cin.fail() checks.

## 4. Review the implementation again

Reread the final code and diff, not just compiler output.

- **Requirements:** requested actions work, scope has not expanded, and active rules
  were preserved. Compare the actual implementation with the initial plan.
- **Simplicity:** no unnecessary components, duplicated actions, or surprising nesting
  remain. Assess call sites and main from the teacher's perspective.
- **Correctness:** check applicable boundaries, overload selection, key changes,
  lifetime, deletion, duplicate keys, and empty states. Do not use this checklist
  as a reason to expand the assignment.
- **Style:** manually inspect spacing, blank lines, Allman braces, aligned comments,
  names, short format calls, and << chains instead of blindly running a formatter.
- **Warnings:** consider clangd/clang-tidy and CLion, not just successful compilation.
  Fix causes first; justify suppression only for a specific false positive.

Run available builds and checks appropriate to the change. For tree/manual ownership
changes, use meaningful scenarios and ASan/UBSan where available. Do not create
artificial tests for cosmetic edits or tests that merely mirror the implementation.
After suitable checks pass, do not broaden them without a new reason. Report only
checks actually run, separating environment limitations from code defects.
Update active project documentation when agreed rules change; preserve history.
Finish with a concise description of the result and actual validation.
