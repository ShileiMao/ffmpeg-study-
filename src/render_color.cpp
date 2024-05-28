#include "render_color.hpp"
bool generate_gradient(uint8_t* start_color, uint8_t* end_color, uint8_t* gradient_out) {
    // create the offscreen buffer and associated Graphics
    int startX = 0;
    int startY = 0;
    int x = startX;
    int y = startY;

    int red = start_color[0], green = start_color[1], blue = start_color[2];

    // 斜边长度(255等分)
    float hypotenuse = (float) (255.0 / cos(M_PI / 4));
    float unitLen = hypotenuse / 255;

    float slopR = (end_color[0] - start_color[0]) / 255.0f;
    float slopG = (end_color[1] - start_color[1]) / 255.0f;
    float slopB = (end_color[2] - start_color[2]) / 255.0f;

    int offX = 0; 
    int offY = 0;

    for (offX = 0; offX < 255; offX++) {
      for (offY = 0; offY < 255; offY ++) {
        x = startX + offX;
        y = startY + offY;

        float diagonallyDistance = (float) ((x + y) * cos(M_PI / 4));
        printf("offx: %d, offY: %d, unitLen: %f\n", offX, offY, unitLen);
        int units = (int) (diagonallyDistance / unitLen);
        int newRed = (int) (red + offX * slopR);
        int newGreen = (int) (green + offY * slopG);
        int newBlue = (int) (blue + units * slopB);

        gradient_out[y * 3 + x * 3 + 0]     = newRed;
        gradient_out[y * 3 + x * 3 + 1]     = newGreen;
        gradient_out[y * 3 + x * 3 + 2]     = newBlue;
      }
    }
    return true;
  }