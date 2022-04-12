import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

public class Solver {
    public static void main(String[] args) {
        System.out.println("Hello");
        double x = 1.1;
        System.out.println(x);
    }

    public static XYDataset picard1Dataset(double n, double h, double x, double y0) {
        XYSeries series = new XYSeries("picard1");
        series.add(x, y0);
        for (int i = 0; i < n - 1; ++i) {
            x += h;
            series.add(x, picard_1(x));
        }
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series);
        return dataset;
    }

    public static XYDataset picard2Dataset(double n, double h, double x, double y0) {
        XYSeries series = new XYSeries("picard2");
        series.add(x, y0);
        double y;
        for (int i = 0; i < n - 1; ++i) {
            x += h;
            y = picard_2(x);
            System.out.printf("%f %f\n", x, y);
            series.add(x, picard_2(x));
        }
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series);
        return dataset;
    }

    public static XYDataset picard3Dataset(double n, double h, double x, double y0) {
        XYSeries series = new XYSeries("picard3");
        series.add(x, y0);
        for (int i = 0; i < n - 1; ++i) {
            x += h;
            series.add(x, picard_3(x));
        }
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series);
        return dataset;
    }

    public static XYDataset picard4Dataset(double n, double h, double x, double y0) {
        XYSeries series = new XYSeries("picard4");
        series.add(x, y0);
        for (int i = 0; i < n - 1; ++i) {
            x += h;
            series.add(x, picard_4(x));
        }
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series);
        return dataset;
    }

    public static XYDataset eulerDataset(double n, double h, double x, double y) {
        XYSeries series = new XYSeries("euler");
        for (int i = 0; i < n; ++i) {
            y += h * f(x, y);
            series.add(x, y);
            x += h;
        }
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series);
        return dataset;
    }


    public static XYDataset rungeKuttaDataset(double n, double h, double x, double y) {
        XYSeries series = new XYSeries("runge kutta");
        double coeff = h / 2.;
        for (int i = 0; i < n; ++i) {
            y += h * f(x + coeff, y + coeff * f(x, y));
            series.add(x, y);
            x += h;
        }
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series);
        return dataset;
    }

    private static double f(double x, double y) {
        return x * x + y * y;
    }

    private static double picard_1(double x) {
        return Math.pow(x, 3) / 3;
    }


    private static double picard_2(double x) {
        return picard_1(x) + Math.pow(x, 7) / 63;
    }


    private static double picard_3(double x) {
        return picard_2(x) +
                2. * Math.pow(x, 11) / 2079. +
                Math.pow(x, 15) / 59535.;
    }


    private static double picard_4(double x) {
        return picard_3(x) +
                2. * Math.pow(x, 15) / 93555. +
                2 * Math.pow(x, 19) / 339495 +
                2 * Math.pow(x, 19) / 2488563. +
                2 * Math.pow(x, 23) / 86266215. +
                Math.pow(x, 23) / 99411543. +
                2 * Math.pow(x, 27) / 3341878155.
                + Math.pow(x, 31) / 109876902975.;
    }
}
