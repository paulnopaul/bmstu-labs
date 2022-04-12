public class EulerDatasetBuilder extends DatasetBuilder{

    public EulerDatasetBuilder(double x0, double y0, double h0, double end) {
        super(x0, y0, h0, end, "euler");
    }

    @Override
    protected void next(int i) {
        if (i > 0) {
            x += h;
        }
        y += h * f(x, y);
    }
}
