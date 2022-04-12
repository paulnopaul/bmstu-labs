import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

public abstract class DatasetBuilder {
    protected double x, y, h;
    protected int n;
    protected double x0, y0;
    protected String name;
    public DatasetBuilder(double x0, double y0, double h0, double end, String name) {
        this.x0 = this.x = x0;
        this.y0 = this.y = y0;
        this.h = h0;
        this.n = (int) Math.ceil(Math.abs(end - x0) / h) + 1;
        this.name = name;
    }

    protected static double f(double x, double y) {
        return x * x + y * y;
    }

    private void start() {
        x = x0;
        y = y0;
    }

    public XYSeriesCollection build() {

        XYSeries series = new XYSeries(name);

        x = x0;
        y = y0;
        for (int i = 0; i < n; ++i) {
            next(i);
            series.add(x, y);
        }

        h = -h;
        x = x0;
        y = y0;
        for (int i = 0; i < n; ++i) {
            next(i);
            series.add(x, y);
        }

        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series);
        return dataset;

    }

    protected abstract void next(int i);
}
