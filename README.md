# Image-Processing
Two algorithms for the Optical Recognition Character (OCR) field.

C++ code for X-Y cut &amp; RLSA  algorithms using QT  as IDE.
 
The XY Cut Algorithm is a method that can be used for Page Segmentation.
The Run Length Smoothing Algorithm (RLSA) is a method that can be used for Block segmentation and text discrimination.

Both of the algorithms can edit images that the lines of the text should be aligned.  
The following image was used  as an example.

![apoleiakartas](https://user-images.githubusercontent.com/32977750/31853166-ebfc99ba-b68c-11e7-805e-6966ed641141.JPG)

X-Y cut has two parts:
1) Finding Lines:Following the produced Image of the function.

![xy_cutlines](https://user-images.githubusercontent.com/32977750/31853312-1d498756-b68f-11e7-88dd-0d791ac8921a.JPG)


2) Finding Words:Following the produced Image of the function.

![xy_cutwords](https://user-images.githubusercontent.com/32977750/31853338-86913de4-b68f-11e7-88ee-5ad0c42b5099.JPG)


RLSA has also two parts:
1) Horizontal RLSA
2) Vertical RLSA
