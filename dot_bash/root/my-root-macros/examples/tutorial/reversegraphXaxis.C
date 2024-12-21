void ReverseXAxis (TGraph *g)
{
   // Remove the current axis
   g->GetXaxis()->SetLabelOffset(999);
   g->GetXaxis()->SetTickLength(0);

   // Redraw the new axis
   gPad->Update();
   TGaxis *newaxis = new TGaxis(gPad->GetUxmax(),
                                gPad->GetUymin(),
                                gPad->GetUxmin(),
                                gPad->GetUymin(),
                                g->GetXaxis()->GetXmin(),
                                g->GetXaxis()->GetXmax(),
                                510,"-SDH");
   newaxis->SetLabelOffset(-0.03);
   newaxis->Draw();
}

void ReverseXGraph (TGraph *g)
{
   // Create a new graph
   Int_t n = g->GetN();
   Double_t *x = g->GetX();
   Double_t *y = g->GetY();
   Double_t xr[100];
   Double_t dx = g->GetXaxis()->GetXmin()+g->GetXaxis()->GetXmax();
   for (Int_t i=0; i<n; i++) {
      xr[i] = -x[i]+dx;
   }

   TGraph *gr = new TGraph(n,xr,y);
   gr->SetMarkerStyle(20);
   gr->SetLineColor(kRed);
   gr->SetMarkerColor(kRed);
   gr->Draw("PL");
}

void reversegraphXaxis ()
{
   const Int_t n = 20;
   Double_t x[n], y[n];
   for (Int_t i=0;i<n;i++) {
      x[i] = i*0.1+5;
      y[i] = 10*sin(x[i]+0.2);
   }
   TGraph *g = new TGraph(n,x,y);
   g->SetMarkerStyle(21);
   g->Draw("APL");

   ReverseXAxis(g);
   ReverseXGraph(g);
}