/**
 * @file FileTests.cpp
 *
 * This module contains the unit tests of the
 * SystemAbstractions::File class.
 *
 * © 2018 by Richard Walters
 */

#include <gtest/gtest.h>
#include <SystemAbstractions/File.hpp>

/**
 * This is the test fixture for these tests, providing common
 * setup and teardown for each test.
 */
struct FileTests
    : public ::testing::Test
{
    // Properties

    /**
     * This is the temporary directory to use to test
     * the File class.
     */
    std::string testAreaPath;

    // Methods

    // ::testing::Test

    virtual void SetUp() {
        testAreaPath = SystemAbstractions::File::GetExeParentDirectory() + "/TestArea";
        ASSERT_TRUE(SystemAbstractions::File::CreateDirectory(testAreaPath));
    }

    virtual void TearDown() {
        ASSERT_TRUE(SystemAbstractions::File::DeleteDirectory(testAreaPath));
    }
};

TEST_F(FileTests, BasicFileMethods) {
    // Check initial conditions:
    // - test area exists
    // - test file doe snot exist
    SystemAbstractions::File testArea(testAreaPath);
    const std::string testFilePath = testAreaPath + "/foo.txt";
    SystemAbstractions::File file(testFilePath);
    ASSERT_FALSE(file.IsExisting());
    ASSERT_FALSE(file.IsDirectory());
    ASSERT_FALSE(file.Open());
    ASSERT_TRUE(testArea.IsExisting());
    ASSERT_TRUE(testArea.IsDirectory());

    // Create file and verify it exists.
    ASSERT_TRUE(file.Create());
    ASSERT_TRUE(file.IsExisting());
    ASSERT_FALSE(file.IsDirectory());
    file.Close();

    // We should be able to open the file now that it exists.
    ASSERT_TRUE(file.Open());
    file.Close();

    // Now destroy the file and verify it not longer exists.
    file.Destroy();
    ASSERT_FALSE(file.IsExisting());

    // Check that we can move the file while it's open.
    ASSERT_TRUE(file.Create());
    ASSERT_TRUE(file.IsExisting());
    ASSERT_EQ(testFilePath, file.GetPath());
    {
        SystemAbstractions::File fileCheck(testFilePath);
        ASSERT_TRUE(fileCheck.IsExisting());
    }
    {
        SystemAbstractions::File fileCheck(testFilePath + "2");
        ASSERT_FALSE(fileCheck.IsExisting());
    }
    ASSERT_TRUE(file.Move(testFilePath + "2"));
    ASSERT_TRUE(file.IsExisting());
    ASSERT_NE(testFilePath, file.GetPath());
    ASSERT_EQ(testFilePath + "2", file.GetPath());
    {
        SystemAbstractions::File fileCheck(testFilePath);
        ASSERT_FALSE(fileCheck.IsExisting());
    }
    {
        SystemAbstractions::File fileCheck(testFilePath + "2");
        ASSERT_TRUE(fileCheck.IsExisting());
    }
    file.Close();
    file.Destroy();
    ASSERT_FALSE(file.IsExisting());

    // Check that we can move the file while it's not open.
    file = std::move(SystemAbstractions::File(testFilePath));
    ASSERT_TRUE(file.Create());
    file.Close();
    ASSERT_TRUE(file.IsExisting());
    ASSERT_EQ(testFilePath, file.GetPath());
    {
        SystemAbstractions::File fileCheck(testFilePath);
        ASSERT_TRUE(fileCheck.IsExisting());
    }
    {
        SystemAbstractions::File fileCheck(testFilePath + "2");
        ASSERT_FALSE(fileCheck.IsExisting());
    }
    ASSERT_TRUE(file.Move(testFilePath + "2"));
    ASSERT_TRUE(file.IsExisting());
    ASSERT_NE(testFilePath, file.GetPath());
    ASSERT_EQ(testFilePath + "2", file.GetPath());
    {
        SystemAbstractions::File fileCheck(testFilePath);
        ASSERT_FALSE(fileCheck.IsExisting());
    }
    {
        SystemAbstractions::File fileCheck(testFilePath + "2");
        ASSERT_TRUE(fileCheck.IsExisting());
    }
    file.Destroy();
    ASSERT_FALSE(file.IsExisting());
}
