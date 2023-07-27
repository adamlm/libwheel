# The Wheel Strongly-Typed Matrix Library

The Wheel Strongly-Typed Matrix library creates a type-safe wraps around a linear algebra matrix type (for now,
`Eigen::Matrix`). This library leverages C++'s strong type system to provide compile-time guarantees that the
operations you perform (or attempt to perform) are mathematically and semantically valid.

## Motivation

Daniel Withopf's presentations on type-safe matrix operations inspired this work. In his lectures, Daniel introduced
dimensioned linear algebra and described how the theory translates to software. He developed a library during his time
at Bosch, but the source code is unavailable. Fortunately, he overviews enough of the high-level interface to aid implementations. For background information, check out Daniel's excellent presentations:

- _Taking Static Type-Safety to the Next Level: Physical Units for Matrices_ - Presented at CppCon 2022
  ([video](https://www.youtube.com/watch?v=aF3samjRzD4&t=2061s),
  [slides](https://raw.githubusercontent.com/CppCon/CppCon2022/main/Presentations/Taking-static-type-safety-to-the-next-level-physical-units-for-matrices-Daniel-Withopf-CppCon-2022.pdf))

- _Taking Static Type-safety to the Next Level: Physical Units for Matrices_ - Presented at CppNow 2022
  ([video](https://www.youtube.com/watch?v=SLSTS-EvOx4))

- _Physical Units for Matrices: How Hard Can It Be?_ - Presented at Meeting C++ 2021
  ([video](https://www.youtube.com/watch?v=4LmMwhM8ODI),
  [slides](https://meetingcpp.com/mcpp/slides/2021/Physical-units-for-matrices6397.pdf))

- _Physical Units for Matrices: How Hard Can It Be?_ - Presented at MUC++ 2021
  ([video](https://www.youtube.com/watch?v=J6H9CwzynoQ))

## Using in your project

1. Add Wheel Strongly-Typed Matrix as a dependency in your project

   ```cmake
   find_package(libwheel_strongly_typed_matrix REQUIRED)
   ```

2. Link against it in your project

   ```cmake
   target_link_libraries(your_project
     PRIVATE
       libwheel::strongly_typed_matrix
   )
   ```
