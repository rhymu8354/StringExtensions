/**
 * @file StringExtensionsTests.cpp
 *
 * This module contains the unit tests of the
 * StringExtensions functions which extend the string library.
 *
 * © 2018-2019 by Richard Walters
 */

#include <gtest/gtest.h>
#include <inttypes.h>
#include <limits>
#include <map>
#include <stdint.h>
#include <string>
#include <StringExtensions/StringExtensions.hpp>
#include <vector>

std::string vsprintfHelper(char const* format, ...) {
    va_list args;
    va_start(args, format);
    const auto result = StringExtensions::vsprintf("%s, %s!", args);
    va_end(args);
    return result;
}

TEST(StringExtensionsTests, vsprintf) {
    ASSERT_EQ("Hello, World!", vsprintfHelper("%s, %s!", "Hello", "World"));
}

TEST(StringExtensionsTests, sprintfBehavesLikeTheStandardCLibrarysVersion) {
    ASSERT_EQ("Hello, World!", StringExtensions::sprintf("%s, %s!", "Hello", "World"));
}

TEST(StringExtensionsTests, sprintfReturnsSomethingComparableToCppString) {
    const std::string expectedOutput = "The answer is 42.";
    ASSERT_EQ(expectedOutput, StringExtensions::sprintf("The answer is %d.", 42));
}

TEST(StringExtensionsTests, wcstombs) {
    ASSERT_EQ("Hello, World!", StringExtensions::wcstombs(L"Hello, World!"));
}

TEST(StringExtensionsTests, Trim) {
    ASSERT_EQ("Hello, World!", StringExtensions::Trim("  \t  \t\t  Hello, World! \r  \n \r\n \t \t\t  "));
}

TEST(StringExtensionsTests, Indent) {
    ASSERT_EQ(
        "Hello, World!\r\n"
        "  This is line 2\r\n"
        "  This is line 3\r\n",
        StringExtensions::Indent(
            "Hello, World!\r\n"
            "This is line 2\r\n"
            "This is line 3\r\n",
            2
        )
    );
    ASSERT_EQ(
        (
            "Struct {\r\n"
            "  field 1\r\n"
            "  field 2\r\n"
            "}"
        ),
        "Struct {"
        + StringExtensions::Indent(
            "\r\nfield 1"
            "\r\nfield 2",
            2
        )
        + "\r\n}"
    );
}

TEST(StringExtensionsTests, ParseComponent) {
    const std::string line = "Value = {abc {x} = def} NextValue = 42";
    ASSERT_EQ(
        "abc {x} = def}",
        StringExtensions::ParseComponent(line, 9, line.length())
    );
}

TEST(StringExtensionsTests, Escape) {
    const std::string line = "Hello, W^orld!";
    ASSERT_EQ(
        "Hello,^ W^^orld^!",
        StringExtensions::Escape(line, '^', {' ', '!', '^'})
    );
}

TEST(StringExtensionsTests, Unescape) {
    const std::string line = "Hello,^ W^^orld^!";
    ASSERT_EQ(
        "Hello, W^orld!",
        StringExtensions::Unescape(line, '^')
    );
}

TEST(StringExtensionsTests, Split_Single_Character_Delimiter) {
    const std::string line = "Hello, World!";
    ASSERT_EQ(
        (std::vector< std::string >{"Hello,", "World!"}),
        StringExtensions::Split(line, ' ')
    );
}

TEST(StringExtensionsTests, Split_Multi_Character_Delimiter) {
    const std::string line = "Hello::World!::This:Day";
    ASSERT_EQ(
        (std::vector< std::string >{"Hello", "World!", "This:Day"}),
        StringExtensions::Split(line, "::")
    );
}

TEST(StringExtensionsTests, Join_Single_Character_Delimiter) {
    const std::vector< std::string > pieces{"Hello", "World!"};
    ASSERT_EQ(
        "Hello:World!",
        StringExtensions::Join(pieces, ':')
    );
}

TEST(StringExtensionsTests, Join_Multi_Character_Delimiter) {
    const std::vector< std::string > pieces{"Hello", "World!"};
    ASSERT_EQ(
        "Hello, World!",
        StringExtensions::Join(pieces, ", ")
    );
}

TEST(StringExtensionsTests, ToLower) {
    EXPECT_EQ("hello", StringExtensions::ToLower("Hello"));
    EXPECT_EQ("hello", StringExtensions::ToLower("hello"));
    EXPECT_EQ("hello", StringExtensions::ToLower("heLLo"));
    EXPECT_EQ("example", StringExtensions::ToLower("eXAmplE"));
    EXPECT_EQ("example", StringExtensions::ToLower("example"));
    EXPECT_EQ("example", StringExtensions::ToLower("EXAMPLE"));
    EXPECT_EQ("foo1bar", StringExtensions::ToLower("foo1BAR"));
    EXPECT_EQ("foo1bar", StringExtensions::ToLower("fOo1bAr"));
    EXPECT_EQ("foo1bar", StringExtensions::ToLower("foo1bar"));
    EXPECT_EQ("foo1bar", StringExtensions::ToLower("FOO1BAR"));
}

TEST(StringExtensionsTests, ToInteger) {
    struct TestVector {
        std::string input;
        intmax_t output;
        StringExtensions::ToIntegerResult expectedResult;
    };
    const auto maxAsString = StringExtensions::sprintf("%" PRIdMAX, std::numeric_limits< intmax_t >::max());
    const auto minAsString = StringExtensions::sprintf("%" PRIdMAX, std::numeric_limits< intmax_t >::lowest());
    auto maxPlusOneAsString = maxAsString;
    size_t digit = maxPlusOneAsString.length();
    while (digit > 0) {
        if (maxPlusOneAsString[digit-1] == '9') {
            maxPlusOneAsString[digit-1] = '0';
            --digit;
        } else {
            ++maxPlusOneAsString[digit-1];
            break;
        }
    }
    if (digit == 0) {
        maxPlusOneAsString.insert(maxPlusOneAsString.begin(), '1');
    }
    auto minMinusOneAsString = minAsString;
    digit = minMinusOneAsString.length();
    while (digit > 1) {
        if (minMinusOneAsString[digit-1] == '9') {
            minMinusOneAsString[digit-1] = '0';
            --digit;
        } else {
            ++minMinusOneAsString[digit-1];
            break;
        }
    }
    if (digit == 1) {
        minMinusOneAsString.insert(maxPlusOneAsString.begin() + 1, '1');
    }
    const std::vector< TestVector > testVectors{
        {"0", 0, StringExtensions::ToIntegerResult::Success},
        {"42", 42, StringExtensions::ToIntegerResult::Success},
        {"-42", -42, StringExtensions::ToIntegerResult::Success},
        {
            maxAsString,
            std::numeric_limits< intmax_t >::max(),
            StringExtensions::ToIntegerResult::Success
        },
        {
            minAsString,
            std::numeric_limits< intmax_t >::lowest(),
            StringExtensions::ToIntegerResult::Success
        },
        {
            maxPlusOneAsString,
            0,
            StringExtensions::ToIntegerResult::Overflow
        },
        {
            minMinusOneAsString,
            0,
            StringExtensions::ToIntegerResult::Overflow
        },
    };
    for (const auto& testVector: testVectors) {
        intmax_t output;
        EXPECT_EQ(
            testVector.expectedResult,
            StringExtensions::ToInteger(
                testVector.input,
                output
            )
        );
        if (testVector.expectedResult == StringExtensions::ToIntegerResult::Success) {
            EXPECT_EQ(
                output,
                testVector.output
            );
        }
    }
}

TEST(StringExtensionsTests, InstantiateTemplate) {
    // Arrange
    const std::string templateText = R"(
Hello, ${who}!
The $10,000 {which you owe ${who}}
is due to \${someone}
$\{when}.  ${something} This one ends ${early
    )";
    const std::map< std::string, std::string > variables{
        {"who", "World"},
        {"when", "tomorrow"},
        {"what", "example"},
    };

    // Act
    const auto instance = StringExtensions::InstantiateTemplate(templateText, variables);

    // Assert
    EXPECT_EQ(
        R"(
Hello, World!
The $10,000 {which you owe World}
is due to ${someone}
$\{when}.   This one ends )",
        instance
    );
}
