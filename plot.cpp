#include "plot.h"

#include <math.h>

Plot::Plot()
{
    this->pen = QPen();
}


Plot::Plot(const Plot &plot) : Plot() {
    const size_t l = plot.size();
    for(size_t i=0;i<l;i++)
        this->add(plot.x_values[i], plot.y_values[i]);
}

Plot::Plot(const QVector<double> &x, const QVector<double> &y) : Plot() {
    this->add(x,y);
}

Plot::~Plot() {

}

QVector<double> Plot::x(void) const {
    QVector<double> ret(this->x_values);
    return ret;
}

QVector<double> Plot::y(void) const {
    QVector<double> ret(this->y_values);
    return ret;
}

void Plot::add(const double x, const double y) {
    this->x_values.push_back(x);
    this->y_values.push_back(y);
}

size_t Plot::add(const QVector<double> &x, const QVector<double> &y) {
    const size_t l = std::min(x.size(), y.size());
    for(size_t i=0;i<l;i++)
        this->add(x[i],y[i]);
    return l;
}

size_t Plot::size(void) const {
    return this->x_values.size();
}

bool Plot::remove(const size_t index) {
    if(index >= size()) return false;
    else {
        this->x_values.remove(index);
        this->y_values.remove(index);
        return true;
    }
}

void Plot::clear(void) {
    this->x_values.clear();
    this->y_values.clear();
}
