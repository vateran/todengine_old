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


//-----------------------------------------------------------------------------
template <typename T>
int TerrainTile::build_connector
(T* ptr, int col, int row, int step,
 int x, int y, int width, int height, int junction)
{
    bool winding = true; 
    int index = 0;

    if (step < 2)
        return 0;

    if (junction == JUNCTION_TOP)
    {
        bool head = false;
        int h = 0;
        while (true)
        {
            if (winding)
            {
                for (int w = 0; w < width; ++w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                    if (!head && w < width - 1)
                    {
                        ptr[index++] = (h * step + y) * col + x + (w * step + step / 2);
                        ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                    }
                }

                head = true;
            }
            else
            {
                for (int w = width - 1; w >= 0; --w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }
            }

            ++h;
            if (h >= height - 1)
                break;
            ptr[index++] = ptr[index - 1];
            winding = !winding;
        }
    }
    else if (junction == JUNCTION_LEFT)
    {
        int h = 0;
        while (true)
        {
            if (winding)
            {
                int w = 0;

                ptr[index++] = (h * step + y) * col + x + (w * step);
                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = (h * step + y) * col + x + ((w + 1)* step);
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                for (w = 1; w < width; ++w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }
                ptr[index++] = ptr[index - 1];
            }
            else
            {
                int w = width - 1;
                for (w = width - 1; w >= 1; --w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }

                ptr[index++] = (h * step + y) * col + x + (w * step);
                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = ptr[index - 1];
                ptr[index++] = ptr[index - 4];
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
            }

            ++h;
            if (h >= height - 1)
                break;            
            winding = !winding;
        }
    }
    else if (junction == JUNCTION_RIGHT)
    {
        int h = 0;
        while (true)
        {
            if (winding)
            {
                int w = 0;
                for (w = 0; w < width - 1; ++w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }

                ptr[index++] = (h * step + y) * col + x + (w * step);
                ptr[index++] = ptr[index - 2];
                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = ptr[index - 2];
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
            }
            else
            {
                int w = width - 1;

                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = (h * step + y) * col + x + (w - 1) * step;
                ptr[index++] = ptr[index - 2];
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                for (w = width - 2; w >= 0; --w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }

                ptr[index++] = ptr[index - 1];
            }

            ++h;
            if (h >= height - 1)
                break;
            winding = !winding;
        }
    }
    else if (junction == JUNCTION_BOTTOM)
    {
        int h = 0;
        while (true)
        {
            if (winding)
            {
                for (int w = 0; w < width; ++w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                    if (h >= height - 2 && w < width - 1)
                    {
                        ptr[index++] = (h * step + y) * col + x + ((w + 1) * step);
                        ptr[index++] = ((h + 1) * step + y) * col + x + (w * step + step / 2);
                    }
                }
            }
            else
            {
                for (int w = width - 1; w >= 0; --w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                    if (h >= height - 2 && w > 0)
                    {
                        ptr[index++] = (h * step + y) * col + x + ((w - 1) * step);
                        ptr[index++] = ((h + 1) * step + y) * col + x + (w * step - step / 2);
                    }
                }
            }

            ++h;
            if (h >= height - 1)
                break;
            ptr[index++] = ptr[index - 1];
            winding = !winding;
        }
    }
    else if (junction == JUNCTION_TOPLEFT)
    {
        bool head = false;
        int h = 0;
        while (true)
        {
            if (winding)
            {
                int w = 0;

                if (!head)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                    ptr[index++] = (h * step + y) * col + x + (w * step + step / 2);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }
                else
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                    ptr[index++] = (h * step + y) * col + x + ((w + 1)* step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }

                for (w = 1; w < width; ++w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                    if (!head && w < width - 1)
                    {
                        ptr[index++] = (h * step + y) * col + x + (w * step + step / 2);
                        ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                    }
                }

                head = true;
            }
            else
            {
                ptr[index++] = ptr[index - 1];

                int w = width - 1;
                for (w = width - 1; w >= 1; --w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }

                ptr[index++] = (h * step + y) * col + x + (w * step);
                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = ptr[index - 1];
                ptr[index++] = ptr[index - 4];
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
            }

            ++h;
            if (h >= height - 1)
                break;            
            winding = !winding;
        }
    }
    else if (junction == JUNCTION_TOPRIGHT)
    {
        bool head = false;
        int h = 0;
        while (true)
        {
            if (winding)
            {
                int w = 0;
                for (w = 0; w < width - 1; ++w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                    if (!head && w < width - 1)
                    {
                        ptr[index++] = (h * step + y) * col + x + (w * step + step / 2);
                        ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                    }
                }

                ptr[index++] = (h * step + y) * col + x + (w * step);
                ptr[index++] = ptr[index - 2];
                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = ptr[index - 2];
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                head = true;
            }
            else
            {
                int w = width - 1;

                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = (h * step + y) * col + x + (w - 1) * step;
                ptr[index++] = ptr[index - 2];
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                for (w = width - 2; w >= 0; --w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }

                ptr[index++] = ptr[index - 1];
            }

            ++h;
            if (h >= height - 1)
                break;
            winding = !winding;
        }
    }
    else if (junction == JUNCTION_BOTTOMLEFT)
    {
        int h = 0;
        while (true)
        {
            if (winding)
            {
                int w = 0;

                ptr[index++] = (h * step + y) * col + x + (w * step);
                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = (h * step + y) * col + x + ((w + 1)* step);
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                if (h >= height - 2)
                {
                    ptr[index++] = (h * step + y) * col + x + ((w + 1) * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step + step / 2);
                }

                for (w = 1; w < width; ++w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }
            }
            else
            {
                int w = 0;
                for (w = width - 1; w >= 1; --w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                    if (h >= height - 2 && w > 1)
                    {
                        ptr[index++] = (h * step + y) * col + x + ((w - 1) * step);
                        ptr[index++] = ((h + 1) * step + y) * col + x + (w * step - step / 2);
                    }
                }

                if (h >= height - 2)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step + step / 2);
                    ptr[index++] = ((h * step + step / 2)+ y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }
                else
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ptr[index - 2];
                    ptr[index++] = ((h * step + step / 2)+ y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }
            }

            ++h;
            if (h >= height - 1)
                break;
            ptr[index++] = ptr[index - 1];
            winding = !winding;
        }
    }
    else if (junction == JUNCTION_BOTTOMRIGHT)
    {
        int h = 0;
        while (true)
        {
            if (winding)
            {
                int w = 0;
                for (w = 0; w < width - 1; ++w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }

                if (h >= height - 2)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1)* step + y) * col + x + (w * step - step / 2);
                    ptr[index++] = ((h * step + step / 2)+ y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }
                else
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ptr[index - 2];
                    ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                    ptr[index++] = ptr[index - 2];
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }
            }
            else
            {
                int w = width - 1;

                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = (h * step + y) * col + x + ((w - 1) * step);
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                if (h >= height - 2)
                {   
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step - step / 2);
                    ptr[index++] = ptr[index - 1];
                }

                for (w = width - 2; w >= 0; --w)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                    if (h >= height - 2 && w > 0)
                    {
                        ptr[index++] = (h * step + y) * col + x + ((w - 1) * step);
                        ptr[index++] = ((h + 1) * step + y) * col + x + (w * step - step / 2);
                    }
                }
            }

            ++h;
            if (h >= height - 1)
                break;
            ptr[index++] = ptr[index - 1];
            winding = !winding;
        }
    }

    return index;
}


//-----------------------------------------------------------------------------
inline int TerrainTile::getLOD() const
{
    return lod_;
}


//-----------------------------------------------------------------------------
inline void TerrainTile::setCenter(const Vector3& center)
{
    center_ = center;
}


//-----------------------------------------------------------------------------
inline const Vector3& TerrainTile::getCenter() const
{
    return center_;
}
