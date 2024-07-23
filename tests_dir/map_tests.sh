#!/bin/zsh

echo "--leak-check=full\n--show-leak-kinds=all\n--track-fds=yes" > .valgrindrc
clear
# cub files in maps/good folder
echo "maps/good/cheese_maze.cub\n"
valgrind ./cub3D maps/good/cheese_maze.cub
echo "maps/good/creepy.cub\n"
valgrind ./cub3D maps/good/creepy.cub
echo "maps/good/dungeon.cub\n"
valgrind ./cub3D maps/good/dungeon.cub
echo "maps/good/library.cub\n"
valgrind ./cub3D maps/good/library.cub
echo "maps/good/matrix.cub\n"
valgrind ./cub3D maps/good/matrix.cub
echo "maps/good/sad_face.cub\n"
valgrind ./cub3D maps/good/sad_face.cub
echo "maps/good/square_map.cub\n"
valgrind ./cub3D maps/good/square_map.cub
echo "maps/good/subject_map.cub\n"
valgrind ./cub3D maps/good/subject_map.cub
echo "maps/good/test_map.cub\n"
valgrind ./cub3D maps/good/test_map.cub
echo "maps/good/test_map_hole.cub\n"
valgrind ./cub3D maps/good/test_map_hole.cub
echo "maps/good/test_pos_bottom.cub\n"
valgrind ./cub3D maps/good/test_pos_bottom.cub
echo "maps/good/test_pos_left.cub\n"
valgrind ./cub3D maps/good/test_pos_left.cub
echo "maps/good/test_pos_right.cub\n"
valgrind ./cub3D maps/good/test_pos_right.cub
echo "maps/good/test_pos_top.cub\n"
valgrind ./cub3D maps/good/test_pos_top.cub
echo "maps/good/test_textures.cub\n"
valgrind ./cub3D maps/good/test_textures.cub
echo "maps/good/test_whitespace.cub\n"
valgrind ./cub3D maps/good/test_whitespace.cub
echo "maps/good/works.cub\n"
valgrind ./cub3D maps/good/works.cub

