# C/C++ Formatting and Implementation Conventions

These preferences apply to the student's coursework. Explicit local agreements
override them. Do not clean up incidental old inconsistencies throughout a repository.

## Files and declarations

- For C++: h and tpp in include/, cpp in src/, entry point in src/main.cpp; each
  domain class has its own file pair. Add ordinary cpp files to the existing build.
- Define constructors and destructors in h, other ordinary methods in cpp.
  Put template definitions in tpp included at the end of the corresponding h.
  This arrangement does not need explicit-instantiation lists or extern template.
  Do not compile tpp separately or include cpp as a substitute for tpp.
- For C, preserve its h/c module structure and valid C syntax. Do not import classes,
  references, this->, or templates from the C++ rules.
- Use UTF-8, LF, four spaces, no tabs or trailing whitespace. End files with a newline.
  Blank lines contain no spaces.
- In C++ headers, #pragma once is the first line. Keep includes together, followed
  by one blank line. In cpp, include its own header first; alphabetical sorting is optional.
- Classes use PascalCase; methods, variables, and fields use snake_case; macros use
  UPPER_SNAKE_CASE; enum class enumerators use PascalCase. Preserve existing C module names.
- Place private before public. Keep fields private and initialize them at declaration.
  Keep getter/setter pairs together. Reading methods are const; input objects usually const&.
- Use this-> in domain classes. A compact container may consistently omit redundant
  this-> when the project agrees; retain this when the current node's address is needed.
- In C++, attach pointer/reference markers to the type: T* object, const T& other,
  T*& node. Do not reformat old C files to that convention without a request.
- Prefer int for indices and counters in custom coursework interfaces. Respect actual
  standard-library result types/ranges at boundaries; do not introduce overflow or
  signed/unsigned warnings merely to follow this preference literally.
- Initialize numeric locals before direct input with = 0 and character buffers with {}.
  Avoid local names that shadow fields: brand_text rather than brand, object rather
  than a container's value field.

## Braces, spaces, and blank lines

- Use Allman braces on separate lines, except short inline constructors with empty {}.
- A single simple statement after if/for/while may omit braces; place the statement
  on the next indented line. Use a block for multiple actions.
- Write if (condition), for (...), switch (...), but function(value). Do not put extra
  spaces inside parentheses or brackets.
- Put one space around binary operators, after commas, and after semicolons in for.
  Unary operators, ->, ::, ., and [] stay adjacent to operands. Use i++ in ordinary loops.
- Separate function definitions with one blank line. A method comment immediately
  precedes its signature; the opening brace immediately follows the signature's line.
  Do not add blank lines immediately after { or before }.
- Separate stages inside a function with one blank line. Keep a prompt next to its
  input. Put one blank line before the final return following substantive work;
  a trivial getter does not need it.
- In h, separate fields, private helpers, constructors, getter/setter pairs, and
  operators. Separate multiline inline methods with one blank line.
- Align case with switch; indent normal case bodies four spaces. Agreed short cases
  such as case 1: object = new Bus; break; can occupy adjacent single lines without
  extra {}. Do not compress a complex case into one line.
- Keep a short constructor initializer list on the signature line; a long list starts
  on the next line with eight spaces. Put the while of do/while on a new line.

## Comments and wrapping

- Keep code comments short and in Russian: «Получение …», «Изменение …», «Вывод …».
  The skill's English instructions do not change the language of code comments.
  In cpp/tpp, put the comment before the definition, starting in column 1.
- In h, put declaration comments on the right. The default // target is column 101,
  aligned with spaces. For a longer declaration, leave at least two spaces before //.
  During local edits, preserve the user's intentional alignment in nearby lines;
  do not reformat the entire header. Align newly added groups consistently.
- Do not comment every obvious body statement. Preserve the assignment block at a
  header's start and sample input after main when that lab uses them.
- Keep short std::format calls on one line, including calls with two arguments.
  For a long call, place arguments on separate lines one indentation level deeper.
  Argument count alone does not justify wrapping.
- Do not wrap << chains just because of line length. Print multiline prompts with
  separate std::cout statements, not adjacent concatenated string literals.
- Use '\n' for ordinary newlines and std::endl when flushing is needed. Do not
  mass-replace existing user-written calls as unrelated cosmetic work.

## Preferred implementation patterns

- Prefer standard algorithms, char_traits, format, and other std facilities unless
  implementing that operation yourself is the learning objective.
- Format tables with std::format, without a custom Table, manual UTF-8 padding,
  or | separators. Put units in parentheses: «Груз (т)», «АКБ (кВт·ч)».
- If a project has String, use its formatter rather than a separate ostringstream
  per field. Do not invent a string class merely for formatting.
- Pass integers to format as numbers, without unnecessary to_string. When changing
  from string to numeric formatting, change the format too: string precision .7
  does not apply to int. Double precision follows the agreed table appearance.
- Print the header separately from table rows. Displayed row numbers must agree
  with operator[]. The user chose zero-based object indices; do not automatically
  renumber menu commands or field enums that start at 1.
- Token-based >> input on one line is sufficient for fields without spaces.
  Do not force getline or a separate line for every field without a reason.
- Friend >>/<< directly implement input/output without delegating to read/write.
  Derived classes first call the immediate base operator through static_cast<Base&>
  or static_cast<const Base&>, then handle their own fields. Do not dispatch a base
  << back into a derived <<; that can recurse.
- Use enum class and named values for field/menu constants instead of magic numbers.
  Move common actions out of switch only when their types and semantics agree.
- By default, main.cpp contains only main, with no free helper functions. Place a
  meaningful shared operation in the appropriate class/module, rather than creating
  interaction/demonstration layers to hide main's complexity.
- Prefer early return/continue over nesting. Prefer auto when initializing from an
  explicit cast, avoiding repetition of the type name.
- Add virtual methods for actual dispatch needs, override for overrides, and a
  virtual destructor for a polymorphic base. Do not make every method virtual.
- Fix shadowing, incorrect override, use-after-free, and noexcept issues instead
  of suppressing CLion/clangd warnings.

Restrictions on smart pointers, stream state, exceptions, tree structure, domain
fields, and menu choices come from the current assignment and project documents.
Do not turn them into universal bans on useful C++ facilities.
