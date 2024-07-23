echo 1
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/color_invalid_rgb.cub
echo 2
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/color_missing.cub
echo 3
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/color_missing_ceiling_rgb.cub
echo 4
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/color_missing_floor_rgb.cub
echo 5
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/color_none.cub
echo 6 
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/empty.cub
echo 7
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/file_letter_end.cub
echo 8 
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/filetype_missing
echo 9 
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/filetype_wrong.buc
echo 10
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/forbidden.cub
echo 11
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/map_first.cub
echo 12
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/map_middle.cub
echo 13
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/map_missing.cub
echo 14
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/map_too_small.cub
echo 15
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/player_multiple.cub
echo 16
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/player_none.cub
echo 17
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/map_only.cub
echo 18
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/player_on_edge.cub
echo 19
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/textures_dir.cub
echo 20
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/textures_duplicates.cub
echo 21
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/textures_forbidden.cub
echo 22
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/textures_invalid.cub
echo 23
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/textures_missing.cub
echo 24
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/textures_none.cub
echo 25
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/textures_not_xpm.cub
echo 26
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/wall_hole_east.cub
echo 27
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/wall_hole_north.cub
echo 28
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/wall_hole_south.cub
echo 29
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/wall_hole_west.cub
echo 30
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/bad/wall_none.cub

