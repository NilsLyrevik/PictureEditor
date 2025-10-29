# Findings

## Sobel + DBSCAN Pipeline

The combination of **Sobel edge detection** followed by **DBSCAN clustering** did not yield meaningful results.

While the visual output appeared interesting, the resulting data was ultimately **unusable** for object detection purposes.

![Demo Animation](findings_visualized/output-eps15.gif)

## ADD ABOUT REMOVEBG HERE
ladidadida

### Analysis

After thresholding, the Sobel edges were **broken and noisy**, causing DBSCAN to group fragmented edge pixels rather than coherent structures.  
This led to increased noise and no clear object-level segmentation or context.


