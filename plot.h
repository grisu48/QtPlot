#ifndef PLOT_H
#define PLOT_H

#include <QVector>
#include <QString>
#include <QPen>
#include <QColor>


/**
 * @brief A single plot
 */
class Plot
{
private:
    /** X coordinates */
    QVector<double> x_values;
    /** Y coordinates */
    QVector<double> y_values;

    /** Indicating if the plot is enabled or not */
    bool enabled = true;
public:
    Plot();
    Plot(const Plot &plot);
    Plot(const QVector<double> &x, const QVector<double> &y);
    virtual ~Plot();

    /**
     * @brief get the x values
     * @return x values
     */
    QVector<double> x(void) const;

    /**
     * @brief get the y values
     * @return y values
     */
    QVector<double> y(void) const;

    /** Pen for this plot */
    QPen pen;

    /**
     * @brief Adds a given point
     * @param x x-coordinate of the point
     * @param y y-coordinate of the point
     */
    void add(const double x, const double y);

    /**
     * @brief Adds the given x and y points. If the number of x and y points are not the same, the procedure takes the minium
     * @param x x-coordinate of the points
     * @param y y-coordinate of the points
     * @returns number of added points
     */
    size_t add(const QVector<double> &x, const QVector<double> &y);

    /**
     * @return the number of points in this plot
     */
    size_t size(void) const;

    /**
     * @brief clear Clears the current plot
     */
    void clear(void);

    /**
     * @brief remove Removes the point with the given index
     * @param index Index of the point to be removed
     * @return true if the element is removed, false if the index is out of bounds
     */
    bool remove(const size_t index);

    size_t readFile(void);

    void setEnabled(const bool enabled) { this->enabled = enabled; }
    bool isEnabled(void) const { return this->enabled; }
};

#endif // PLOT_H
