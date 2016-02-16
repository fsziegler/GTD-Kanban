(first cut)

Building Boost with MinGW on Windows:

From c:\dev\boost_1_60_0:
bootstrap
bjam --toolset=gcc  --build-dir=c:\dev\boost_1_60_0\build --build-type=complete  stage
b2 toolset=gcc --build-dir=c:\dev\boost_1_60_0\build --build-type=minimal  stage
