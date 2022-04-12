public class RungeKuttaDatasetBuilder extends DatasetBuilder{
    double coeff;
    public RungeKuttaDatasetBuilder(double x0, double y0, double h0, double end) {
        super(x0, y0, h0, end, "runge kutta");
        coeff = h / 2.;
    }

    @Override
    protected void next(int i) {
        if (i > 0) {
            x += h;
        }
        y += h * f(x + coeff, y + coeff * f(x, y));
    }
}
