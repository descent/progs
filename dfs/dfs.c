#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

typedef struct point_
{
  int row;
  int col;
}Point;

int maze[MAX_ROW][MAX_COL]=
{
  0,1,0,0,0,
  0,1,0,1,0,
  0,0,0,0,0,
  0,1,1,1,0,
  0,0,0,1,0
};

Point predecessor[MAX_ROW][MAX_COL]=
{
  {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}},
  {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}},
  {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}},
  {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}},
  {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}}
};

void print_maze(void)
{
  int i, j;
  for (i=0 ; i < MAX_ROW ; ++i)
  {
    for (j=0 ; j < MAX_COL ; ++j)
    {
      printf("%d ", maze[i][j]);
    }
    putchar('\n');
  }
  printf("******\n");
}


Point stack[512];

int top=0;

void push(Point p)
{
  stack[top++] = p;
}

Point pop(void)
{
  return stack[--top];
}

int is_empty(void)
{
  return (top == 0);
}

void visit(int row, int col, Point pre)
{
  Point visit_point = {row, col};
  maze[row][col] = 2;
  predecessor[row][col] = pre;
  push(visit_point);
}

int main(int argc, char *argv[])
{
  Point p = {0, 0};  

  maze[p.row][p.col] = 2;
  push(p);

  while(!is_empty())
  {
    p = pop();
    // find the path
    if (p.row == MAX_ROW -1 && p.col == MAX_COL -1)
    {
      break;
    }
    // right
    if ((p.col + 1) < MAX_COL && maze[p.row][p.col+1] == 0)
    {
      visit(p.row, p.col+1, p);
    }
    // down
    if ((p.row + 1) < MAX_ROW && maze[p.row+1][p.col] == 0)
    {
      visit(p.row+1, p.col, p);
    }
    // left
    if ((p.col - 1) >= 0 && maze[p.row][p.col-1] == 0)
    {
      visit(p.row, p.col-1, p);
    }

    // up
    if ((p.row - 1) >= 0 && maze[p.row - 1][p.col] == 0)
    {
      visit(p.row-1, p.col, p);
    }

    print_maze();
  }
  if (p.row == MAX_ROW - 1 && p.col == MAX_COL - 1)
  {
    printf("(%d, %d)\n", p.row, p.col);
    while(predecessor[p.row][p.col].row != -1)
    {
      p = predecessor[p.row][p.col];
      printf("(%d, %d)\n", p.row, p.col);
    }
  }
  else
  {
    printf("No path!\n");
  }
  return 0;
}
