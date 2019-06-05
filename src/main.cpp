#include <stdio.h>
#include "libyuv.h"

using namespace libyuv;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("example\n   %s 640x480 yuvfile argbfile\n", argv[0]);
        return -1;
    }

    int ret;

    int width, height;
    sscanf(argv[1], "%dx%d", &width, &height);

    char *yuv_file_path = argv[2];
    char *argb_file_path = argv[3];

    FILE *fp = fopen(yuv_file_path, "rb");
    if (!fp)
    {
        printf("failed to read file in path: %s\n", yuv_file_path);
        return -1;
    }

    int y_buf_size = width * height;
    uint8_t y_buf[y_buf_size];

    ret = fread(y_buf, 1, y_buf_size, fp);
    if (ret != y_buf_size)
    {
        printf("failed to read y data.\n");
        return -1;
    }

    int vu_buf_size = width * height / 2;
    uint8_t vu_buf[vu_buf_size];

    ret = fread(vu_buf, 1, vu_buf_size, fp);
    if (ret != vu_buf_size)
    {
        printf("failed to read vu data.\n");
        return -1;
    }

    fclose(fp);

    int argb_size = width * height * 4;
    uint8_t argb_buf[argb_size];

    ret = NV21ToARGB(y_buf, width, vu_buf, width, argb_buf, width * 4, width, height);
    if (ret != 0)
    {
        printf("failed to NV21ToARGB. %d\n", ret);
        return -1;
    }

    FILE *out_file = fopen(argb_file_path, "wb");
    if (!out_file)
    {
        printf("failed to create argb file.\n");
        return -1;
    }

    ret = fwrite(argb_buf, 1, argb_size, out_file);
    if (ret < 0)
    {
        printf("failed to write argb to file. %d\n", ret);
        return -1;
    }

    fclose(out_file);

    printf("convert success.\n");

    return 0;
}