public class RungeKuttaDatasetBuilder extends DatasetBuilder{
    double a;
    public RungeKuttaDatasetBuilder(double x0, double y0, double h0, double end, double c) {
        super(x0, y0, h0, end, "runge kutta");
        a = c;
    }

    @Override
    protected void next(int i) {
        if (i > 0) {
            x += h;
        }
        y += h * ((1 - a) * f(x, y) + a * f(x + h/(2 * a), y + h * f(x, y) / (a * 2)));
    }
}
