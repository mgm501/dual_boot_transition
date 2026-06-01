void rootpractice()
{

	TH1F *hist = new TH1F("hist", "Practice", 100, 0, 100);

	hist->Fill(10);
	
	TCanvas *histogram = new TCanvas("histogram", "Canvas", 800, 600);
	new TCanvas;
	h1->Draw();
}
