#ifndef GRIDBAGLAYOUT_H_
#define GRIDBAGLAYOUT_H_

#include <stddef.h>
#include <vector>
struct GridInsets {
	float top;
	float left;
	float bottom;
	float right;
	GridInsets() : top(0),left(0),bottom(0),right(0) { };
	GridInsets(float t,float l, float b, float r) : top(t),left(l),bottom(b),right(r) { };
};

struct GridBagConstraints {
    int gridx;
    int gridy;
    int gridwidth;
    int gridheight;
    double weightx;
    double weighty;
    enum _Anchor {
      CENTER=0, NORTH, NORTHEAST,EAST,SOUTHEAST,SOUTH,SOUTHWEST,WEST,NORTHWEST
    } anchor;
    enum _FillMode {
    	NONE=0,BOTH,HORIZONTAL,VERTICAL
    } fill;
    GridInsets insets;
    float ipadx;
    float ipady;
    float tempX;
    float tempY;
    float tempWidth;
    float tempHeight;
    float minWidth;
    float minHeight;
    float aminWidth,aminHeight;
    float prefWidth,prefHeight;


    GridBagConstraints() {
        gridx = -1;
        gridy = -1;
        gridwidth = 1;
        gridheight = 1;

        weightx = 0;
        weighty = 0;
        anchor = CENTER;
        fill = NONE;

        insets = GridInsets(0, 0, 0, 0);
        ipadx = 0;
        ipady = 0;

        prefWidth=prefHeight=minWidth=minHeight=aminWidth=aminHeight=-1;
        tempHeight=tempWidth=tempX=tempY=0;
    }

    GridBagConstraints(int gridx, int gridy,
                              int gridwidth, int gridheight,
                              double weightx, double weighty,
							  _Anchor anchor, _FillMode fill,
                              GridInsets insets, float ipadx, float ipady) {
        this->gridx = gridx;
        this->gridy = gridy;
        this->gridwidth = gridwidth;
        this->gridheight = gridheight;
        this->fill = fill;
        this->ipadx = ipadx;
        this->ipady = ipady;
        this->insets = insets;
        this->anchor  = anchor;
        this->weightx = weightx;
        this->weighty = weighty;

        prefWidth=prefHeight=minWidth=minHeight=aminWidth=aminHeight=-1;
        tempHeight=tempWidth=tempX=tempY=0;
    }

    bool isVerticallyResizable() {
        return (fill == BOTH || fill == VERTICAL);
    }
};

struct GridBagLayoutInfo {
    int width, height;          /* number of  cells: horizontal and vertical */
    int startx, starty;         /* starting point for layout */
    std::vector<float> minWidth;             /* largest minWidth in each column */
    std::vector<float> minHeight;            /* largest minHeight in each row */
    std::vector<double> weightX;           /* largest weight in each column */
    std::vector<double> weightY;           /* largest weight in each row */
    GridBagLayoutInfo(int width, int height) : startx(0), starty(0), minWidth(), minHeight(),weightX(),weightY() {
        this->width = width;
        this->height = height;
    }
    GridBagLayoutInfo() : width(-1), height(-1), startx(0), starty(0), minWidth(), minHeight(),weightX(),weightY()
    {
    }
};

class Sprite;
class GridBagLayout {
    GridBagConstraints defaultConstraints;
    GridBagLayoutInfo layoutInfo;
    Sprite *componentAdjusting;
protected:
    struct Rectangle {
    	float x,y,width,height;
    	Rectangle(): x(0),y(0),width(0),height(0) { }
    };
    GridBagConstraints *lookupConstraints(Sprite *comp);
    /*void getLayoutOrigin (float &x,float &y);
    void getLayoutDimension(float *wdim,float *hdim,int &wsize, int &hsize);
    void getLayoutWeights(double *wdim,double *hdim,int &wsize, int &hsize);*/
    void preInitMaximumArraySizes(Sprite *parent,size_t &a0,size_t &a1);
    void AdjustForGravity(GridBagConstraints *constraints, Rectangle &r);
public:
    std::vector<float> columnWidths;
    std::vector<float> rowHeights;
    std::vector<double> columnWeights;
    std::vector<double> rowWeights;
    GridInsets pInsets;
    bool dirty;
    GridBagLayoutInfo getLayoutInfo(Sprite *parent, int sizeflag);
    void getMinSize(Sprite *parent, GridBagLayoutInfo info, float &w,float &h, GridInsets &insets);
    void ArrangeGrid(Sprite *parent);
    GridBagLayoutInfo *getCurrentLayoutInfo() { return &layoutInfo; }
};

#endif /* GRIDBAGLAYOUT_H_ */
