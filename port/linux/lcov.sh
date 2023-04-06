lcov --capture --directory build/package/pikascript/CMakeFiles/pikascript-core.dir/pikascript-core --directory build/package/pikascript/CMakeFiles/pikascript-core.dir/pikascript-lib/*/ --output-file  testHtml.info --test-name testHtml

genhtml -o result testHtml.info

