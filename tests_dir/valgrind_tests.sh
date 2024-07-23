echo 1 
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/color_256.cub
echo 2
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/color_alphabet.cub
echo 3
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/color_duplicate.cub
echo 4
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/color_empty.cub
echo 5
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/color_missingblue.cub
echo 6
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/color_negative.cub
echo 7
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/color_nocomma.cub
echo 8
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/color_undermap.cub
echo 9
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/color_wrongidentifier.cub
echo 10
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/empty.cub
echo 11
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/map_empty.cub
echo 12
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/map_invalidchar.cub
echo 13
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/map_missing_player.cub
echo 14 
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/map_unwarppedE.cub
echo 15 
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/map_unwarppedN.cub
echo 16 
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/map_unwarppedS.cub
echo 17 
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/map_unwarppedW.cub
echo 18
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/map_wrongplayer.cub
echo 19
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/tex_empty.cub
echo 20
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/tex_invalidchars.cub
echo 21
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/tex_missingfile.cub
echo 22
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/tex_missingside.cub
echo 23
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/tex_pathgaps.cub
echo 24
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/tex_undermap.cub
echo 25
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/invalid/test_file.cub
