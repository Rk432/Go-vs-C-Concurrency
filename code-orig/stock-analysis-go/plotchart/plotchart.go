package plotchart

import (
	// "fmt"
	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg"
)

func PlotMACDChart(data []float64, filename string) error {
	p := plot.New()

	points := make(plotter.XYs, len(data))
	for i := range data {
		points[i].X = float64(i + 1)
		points[i].Y = data[i]
	}

	line, err := plotter.NewLine(points)
	if err != nil {
		return err
	}
	p.Add(line)

	p.Title.Text = "MACD Chart"
	p.X.Label.Text = "Day"
	p.Y.Label.Text = "MACD Value"

	if err := p.Save(6*vg.Inch, 4*vg.Inch, filename); err != nil {
		return err
	}

	// fmt.Printf("MACD chart saved as %s\n", filename)
	return nil
}
