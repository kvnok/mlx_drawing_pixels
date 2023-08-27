#include "stuff.h"
#define SIZE 640

int32_t pixel_select(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void make_square(t_data *data)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < data->img->height)
	{
		x = 0;
		while (x < data->img->width)
		{
			mlx_put_pixel(data->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

void coords_setup(t_data *data)
{
	data->x1 = rand() % SIZE;
	data->y1 = rand() % SIZE;
	data->x2 = rand() % SIZE;
	data->y2 = rand() % SIZE;
	data->color = pixel_select(
		rand() % 255,
		rand() % 255,
		rand() % 255,
		255
	);
}

void draw_line(t_data *data)
{
	int x1 = data->x1;
	int y1 = data->y1;
	int x2 = data->x2;
	int y2 = data->y2;
	int x = 1;
	int y = 1;
	if (x1 > x2)
		x = -1;
	if (y1 > y2)
		y = -1;
	while(x1 != x2 || y1 != y2)
	{
		mlx_put_pixel(data->img, x1, y1, data->color);
		if (x1 != x2)
			x1 += x;
		if (y1 != y2)
			y1 += y;
	}
}

void loop_hook_function(void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (data->go == true)
	{
		coords_setup(data);
		draw_line(data);
	}
}

void ft_on_key(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = (t_data *)param;

	//press once
	if (keydata.action == MLX_PRESS)
	{
		//close window, exit program
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(data->mlx);
			mlx_terminate(data->mlx);
			exit(0);
		}
		//put screen to black
		if (keydata.key == MLX_KEY_Q)
			make_square(data);
		//start generating lines
		if (keydata.key == MLX_KEY_W)
			data->go = true;
		//stop generating lines
		if (keydata.key == MLX_KEY_E)
			data->go = false;
	}
	if (keydata.action == MLX_REPEAT)
	{
		//manually keeping the generating going
		if (keydata.key == MLX_KEY_R)
		{
			coords_setup(data);
			draw_line(data);
		}
	}
}

int main(int argc, char **argv)
{
	t_data data;

	data.mlx = mlx_init(SIZE, SIZE, "drawing_the_pixels", false);
	data.img = mlx_new_image(data.mlx, SIZE, SIZE);
	data.go = false;
	mlx_loop_hook(data.mlx, loop_hook_function, &data);
	mlx_key_hook(data.mlx, &ft_on_key, &data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return 0;
}
