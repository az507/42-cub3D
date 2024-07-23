echo 1 standard
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/standard.cub
echo 2 spawn_north
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/spawn_north.cub
echo 3 spawn_south
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/spawn_south.cub
echo 4 spawn_west
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/spawn_west.cub
echo 5 spawn_east
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/spawn_east.cub
echo 6 tex_variety
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/tex_variety.cub
echo 7 tex_512
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/tex_512.cub
echo 8 tex_big
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/tex_big.cub
echo 9 tex_bigger
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/tex_bigger.cub
echo 10 format_spaces_mixed_order
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/format_spaces_mixed_order.cub
echo 11 map_nonzero_spaces
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/map_nonzero_spaces.cub
echo 12 map2
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/map2.cub
echo 13 map_smallest
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/map_smallest.cub
echo 14 map_large
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/map_large.cub
