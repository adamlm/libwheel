# Contributing to the Wheel Library

## Table of contents

- [Quick links](#quick-links)
- [How to report issues](#how-to-propose-enhancements)
- [How to propose enhancements](#how-to-propose-enhancements)
- [How to submit changes](#how-to-submit-changes)
- [Style guides](#style-guides)

## Quick links

- [Documentation](https://example.com) (coming soon)
- [Issue tracker][issue_tab_link]
- [Discussions][discussion_tab_link]

## How to report issues

Please open an [issue][issue_tab_link] using the appropriate template.

## How to propose enhancements

Please open an [issue][issue_tab_link] using the _enhancement_ template.

## How to submit changes

The Wheel Library uses a [forking workflow][forking_workflow_link] for external contributions. When you are ready to
submit your changes for review and integration, please open a pull request from your fork repository to this
repository. Make sure your pull request has a corresponding open issue, otherwise your submission may be rejected.

## Style guides

### General style guide

- Unless otherwise required, file names should be all lowercase with underscores (`_`) separating each word.
- Files should end with a single empty line.
- Lines should not have trailing whitespace.

### C++ style guide

The Wheel Library mixes styles from Google, LLVM, and the C++ Standard library. We use [ClangFormat][clang_format_link]
to assist with auto formatting the code. Check out the `.clang-format` file in the repository's root to see the
specific style settings. Some rules worth mentioning (and that can't be auto-formatted or checked) include:

- Class names should, in general, use `PascalCase` or `UpperCamelCase`. Meta-functions, niebloids, and function objects
  are notable exceptions that use `snake_case`.
- Function names should use `snake_case`.

### CMake style guide

In general, the Wheel Library uses the formatting conventions that Craig Scott uses in his book
[_Professional CMake: A Practical Guide_][professional_cmake_link]. Specific rules, either inspired by or taken from
that book include:

- Function and macro names should use `snake_case`.
- Indentations should have a width of 2 and use `[SPACE]` characters instead of `[TAB]` characters.

[issue_tab_link]: https://github.com/adamlm/libwheel/issues
[discussion_tab_link]: https://github.com/adamlm/libwheel/discussions
[forking_workflow_link]: https://www.atlassian.com/git/tutorials/comparing-workflows/forking-workflow
[clang_format_link]: https://clang.llvm.org/docs/ClangFormat.html
[professional_cmake_link]: https://crascit.com/professional-cmake/
