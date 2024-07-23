#!/bin/zsh

echo "--leak-check=full\n--show-leak-kinds=all\n--track-fds=yes\n" > .valgrindrc

echo "./test_abc_dir/cub_files/alternate.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/alternate.cub
echo "./test_abc_dir/cub_files/arrow.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/arrow.cub
echo "./test_abc_dir/cub_files/big_nbr.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/big_nbr.cub
echo "./test_abc_dir/cub_files/binary_file.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/binary_file.cub
echo "./test_abc_dir/cub_files/island.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/island.cub
echo "./test_abc_dir/cub_files/rubbish.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/rubbish.cub
echo "./test_abc_dir/cub_files/abc.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/abc.cub
echo "./test_abc_dir/cub_files/slope.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/slope.cub
echo "./test_abc_dir/cub_files/test1.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test1.cub
echo "./test_abc_dir/cub_files/test2.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test2.cub
echo "./test_abc_dir/cub_files/test3.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test3.cub
echo "./test_abc_dir/cub_files/test4.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test4.cub
echo "./test_abc_dir/cub_files/test5.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test5.cub
echo "./test_abc_dir/cub_files/test6.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test6.cub
echo "./test_abc_dir/cub_files/test7.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test7.cub
echo "./test_abc_dir/cub_files/test8.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test8.cub
echo "./test_abc_dir/cub_files/test9.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test9.cub
echo "./test_abc_dir/cub_files/test10.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test10.cub
echo "./test_abc_dir/cub_files/test11.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test11.cub
echo "./test_abc_dir/cub_files/test.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/test.cub
echo "./test_abc_dir/cub_files/uneven.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/uneven.cub
echo "./test_abc_dir/cub_files/xpm_file_with_long_name.cub\n"
valgrind ./cub3D ./test_abc_dir/cub_files/xpm_file_with_long_name.cub
echo "./test_abc_dir/cub_files/long_horizontal_line.cub\n"
echo "may need to change get_next_line buffer_size for this\n"
valgrind ./cub3D ./test_abc_dir/cub_files/long_horizontal_line.cub
echo "./test_abc_dir/cub_files/long_vertical_line.cub\n"
echo "may need to change get_next_line buffer_size for this\n"
valgrind ./cub3D ./test_abc_dir/cub_files/long_vertical_line.cub
echo "./test_abc_dir/cub_files/wall.cub\n"
echo "may need to change get_next_line buffer_size for this\n"
valgrind ./cub3D ./test_abc_dir/cub_files/wall.cub

