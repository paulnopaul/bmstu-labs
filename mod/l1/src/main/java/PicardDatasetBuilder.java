public class PicardDatasetBuilder extends DatasetBuilder {

    int num;

    public PicardDatasetBuilder(double x0, double y0, double h0, double end, int num) {
        super(x0, y0, h0, end, "picard " + String.valueOf(num));
        this.num = num;
    }

    @Override
    protected void next(int i) {
        if (i > 0) {
            x += h;
            switch (num) {
                case 1:
                    y = picard_1(x);
                    break;
                case 2:
                    y = picard_2(x);
                    break;
                case 3:
                    y = picard_3(x);
                    break;
                case 4:
                    y = picard_4(x);
                    break;
            }
        }
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
        return picard_2(x) +
                2. * Math.pow(x, 11) / 2079. +
                13. * Math.pow(x, 15) / 218295. +
                82. * Math.pow(x, 19) / 37328445. +
                662 * Math.pow(x, 23) / 10438212015. +
                4 * Math.pow(x, 27) / 3341878155. +
                Math.pow(x, 31) / 109876902975.;
    }
}
