/*
 * Hint : There is only a mistake, might not be exploitable :)
 */

class Shape {
public:
  int x;
  int y;
  virtual ~Shape();
};

int main()
{
    Shape *s = new Shape;
    s->x = 1;
    s->y = 2;
    Shape *t = new Shape;
    memcpy(dest, source, sizeof Shape);
    printf("%d %d", t->x, t->y);
}