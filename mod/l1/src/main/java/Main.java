import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.block.BlockBorder;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.chart.title.TextTitle;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.Font;

public class Main extends JFrame {

    public Main() {
        initUI();
    }

    private void initUI() {

        JFreeChart chart = createChart();

        ChartPanel chartPanel = new ChartPanel(chart);

        chartPanel.setBorder(BorderFactory.createEmptyBorder(15, 15, 15, 15));
        chartPanel.setBackground(Color.white);

        add(chartPanel);

        pack();
        setTitle("Line chart");
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    /*
    private XYDataset createDataset(int i) {
        double h = Math.pow(10, -2);
        double x0 = 0;
        double y0 = 0;
        double end = 2.0;


         pic1 = new PicardDatasetBuilder(x0, y0, h, end, 1).build();
         pic2= new PicardDatasetBuilder(x0, y0, h, end, 2).build();
         pic3= new PicardDatasetBuilder(x0, y0, h, end, 3).build();
         pic4= new PicardDatasetBuilder(x0, y0, h, end, 4).build();
         euler= new EulerDatasetBuilder(x0, y0, h, end).build();
         runge= new RungeKuttaDatasetBuilder(x0, y0, h, end, 1).build();

        switch (i) {
            case 1: return pic2;
            case 2: return pic3;
            case 3: return pic4;
            case 4: return euler;
            case 5: return runge;
            default:
                return pic1;
        }

    }
    */

    private JFreeChart createChart() {
        double h = Math.pow(10, -4);
        double x0 = 0;
        double y0 = 0;
        double end = 2.0;


        XYSeriesCollection x = new XYSeriesCollection();

        XYSeries pic1 = new PicardDatasetBuilder(x0, y0, h, end, 1).build();
        x.addSeries(pic1);

//        XYSeries pic2= new PicardDatasetBuilder(x0, y0, h, end, 2).build();
//        x.addSeries(pic2);

//        XYSeries pic3= new PicardDatasetBuilder(x0, y0, h, end, 3).build();
//        x.addSeries(pic3);

//        XYSeries pic4= new PicardDatasetBuilder(x0, y0, h, end, 4).build();
//        x.addSeries(pic4);

//        XYSeries euler= new EulerDatasetBuilder(x0, y0, h, end).build();
//        x.addSeries(euler);

//        XYSeries runge= new RungeKuttaDatasetBuilder(x0, y0, h, end, 0.5).build();
//        x.addSeries(runge);



        JFreeChart chart = ChartFactory.createXYLineChart(
                "Mathematics",
                "X",
                "Y",
                x,
                PlotOrientation.VERTICAL,
                true,
                true,
                false
        );

        XYPlot plot = chart.getXYPlot();

        XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer();

        renderer.setSeriesPaint(0, Color.RED);
        renderer.setSeriesStroke(0, new BasicStroke(1.0f));
        renderer.setSeriesShapesVisible(0, Boolean.FALSE);

        renderer.setSeriesPaint(1, Color.BLUE);
        renderer.setSeriesStroke(1, new BasicStroke(1.0f));
        renderer.setSeriesShapesVisible(1, Boolean.FALSE);

        renderer.setSeriesPaint(2, Color.ORANGE);
        renderer.setSeriesStroke(2, new BasicStroke(1.0f));
        renderer.setSeriesShapesVisible(2, Boolean.FALSE);

        renderer.setSeriesPaint(3, Color.BLACK);
        renderer.setSeriesStroke(3, new BasicStroke(1.0f));
        renderer.setSeriesShapesVisible(3, Boolean.FALSE);

        renderer.setSeriesPaint(4, Color.YELLOW);
        renderer.setSeriesStroke(4, new BasicStroke(1.0f));
        renderer.setSeriesShapesVisible(4, Boolean.FALSE);

        renderer.setSeriesPaint(5, Color.CYAN);
        renderer.setSeriesStroke(5, new BasicStroke(1.0f));
        renderer.setSeriesShapesVisible(5, Boolean.FALSE);

        plot.setRenderer(renderer);
        plot.setBackgroundPaint(Color.white);

        plot.setRangeGridlinesVisible(true);
        plot.setRangeGridlinePaint(Color.BLACK);

        plot.setDomainGridlinesVisible(true);
        plot.setDomainGridlinePaint(Color.BLACK);


        chart.getLegend().setFrame(BlockBorder.NONE);

        chart.setTitle(new TextTitle("methods",
                        new Font("Serif", java.awt.Font.BOLD, 18)
                )
        );

        return chart;
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            Main ex = new Main();
            ex.setVisible(true);
        });
    }
}