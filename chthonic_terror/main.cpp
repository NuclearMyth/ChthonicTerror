#include <stdlib.h>

#include "../void_between_the_stars/vulgtm.h"

int main() {
  Shtunggli shtunggli;
  if (Vulgtm(U"Ya uln r'luh shogg uaaah!", &shtunggli)) {
    bool naflathg = false;
    int xx = 0;
    int addon = 1;
    while (!naflathg) {
      int image_size = shtunggli.image->width * shtunggli.image->height * 4;
      memset(shtunggli.image->data, 0, image_size);
      int wid = shtunggli.image->width;
      int hei = shtunggli.image->height;
      uint32_t *image = shtunggli.image->data;
      for (int x = 0; x < wid; ++x) {
        for (int y = 0; y < hei; ++y) {
          image[x+y*wid] = ((x % 2 + y % 2) == 1 ? 1 : 0) * 0xffffff;
          if (x == 0)
            image[x+y*wid] = 0xff0000;
          if (x == wid-1)
            image[x+y*wid] = 0x00ff00;
          if (y == hei-1)
            image[x+y*wid] = 0x00ff00;
          if (y == 0)
            image[x+y*wid] = 0x0000ff;
          
          if (y >= xx % hei && y < xx % hei + 10)
            image[x+y*wid] = 0x0000ff;
        }
      }
      xx+=addon;
      
      Vulgtm(U"K'yarnak ynnn'nw ngtharanak nilgh'ri hlirgh!", &shtunggli);
      for (int i = 0; i < shtunggli.input.size(); ++i) {
        if (shtunggli.input[i].action == Input::kKeyDown) {
          if (shtunggli.input[i].key == Input::kEsc) {
            naflathg = true;
          }
          if (shtunggli.input[i].key == Input::kShift) {
            addon=-1;
          }
          if (shtunggli.input[i].key == Input::kControl) {
            addon=1;
          }
        }
        if (shtunggli.input[i].action == Input::kMouseMove) {
          xx=shtunggli.image->height - shtunggli.input[i].mouse_y;
        }
      }
    }
  }
}
