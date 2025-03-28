#include "parser.h"

void    make_obj_data(char **split)
{
    t_obj  *obj;
    t_obj  *new;
    
    obj = set_get_obj(GET, NULL);
    new = (t_obj *)safe_malloc(1, sizeof(t_obj));
    init_obj(new);
    if (ft_memcmp(split[0], "pl", 3) == 0)
        set_pl_data(split, new);
    if (ft_memcmp(split[0], "sp", 3) == 0)
        set_sp_data(split, new);
    if (ft_memcmp(split[0], "cy", 3) == 0) 
        set_cy_data(split, new);
    obj_lst_add_back(obj, new);
}

void    set_pl_data(char **split, t_obj *obj)
{
    double  xyz[3];
    double  vector[3];
    double  rgb[3];

    if (count_split(split) != 4)
        print_error_and_exit("set_pl_data", "number of arguments is not 4");
    obj->id = PL;
    set_array(split[1], xyz, OTHER);
    set_struct_xyz(&obj->xyz, xyz);
    set_array(split[2], vector, VECTOR);
    set_struct_xyz(&obj->vector, vector);
    set_array(split[3], rgb, RGB);
    obj->rgb = make_trgb(0, rgb[0], rgb[1], rgb[2]);
}

void    set_sp_data(char **split, t_obj *data)
{
    double  xyz[3];
    double  rgb[3];

    if (count_split(split) != 4)
        print_error_and_exit("set_sp_data", "number of arguments is not 4");
    data->id = SP;
    set_array(split[1], xyz, OTHER);
    set_struct_xyz(&data->xyz, xyz);
    data->diameter = ft_atof(split[2]);
    if (data->diameter < 0)
       print_error_and_exit("set_sp_data", "diameter shuold be over 0"); 
    set_array(split[3], rgb, RGB);
    data->rgb = make_trgb(0, rgb[0], rgb[1], rgb[2]);
}

void    set_cy_data(char **split, t_obj *obj)
{
    double  xyz[3];
    double  vector[3];
    double  rgb[3];


    if (count_split(split) != 6)
        print_error_and_exit("set_cy_data", "number of arguments is not 6");
    obj->id = CY;
    set_array(split[1], xyz, OTHER);
    set_struct_xyz(&obj->xyz, xyz);
    set_array(split[2], vector, VECTOR);
    set_struct_xyz(&obj->vector, vector);
    obj->diameter = ft_atof(split[3]);
    if (obj->diameter < 0)
       print_error_and_exit("set_cam_data", "diameter shuold be over 0");
    obj->height = ft_atof(split[4]); 
    if (obj->height < 0)
       print_error_and_exit("set_cam_data", "height shuold be over 0");
    set_array(split[5], rgb, RGB);
    obj->rgb = make_trgb(0, rgb[0], rgb[1], rgb[2]);
}

void    obj_lst_add_back(t_obj *obj, t_obj *new)
{
    if (!obj)
    {
        obj = new;
        set_get_obj(SET, obj);
        return ;
    }
    while (obj->next)
        obj = obj->next;
    obj->next = new;
}
