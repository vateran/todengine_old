//-----------------------------------------------------------------------------
template <typename T>
int TerrainTile::build_index
(T* ptr, int col, int row, int step,
 int x, int y, int width, int height)
{
    bool winding = true; 
    int index = 0;

    int h = 0;
    while (true)
    {
        if (winding)
        {
            for (int w = 0; w < width; w += 1)
            {
                ptr[index++] = (h * step + y) * col + x + (w * step);
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
            }
        }
        else
        {
            for (int w = width - 1; w >= 0; w -= 1)
            {
                ptr[index++] = (h * step + y) * col + x + (w * step);
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
            }
        }

        h += 1;
        if (h >= height - 1)
            break;
        ptr[index++] = ptr[index - 1];

        winding = !winding;
    }

    return index;
}
