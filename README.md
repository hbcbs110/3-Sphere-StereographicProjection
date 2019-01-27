# 3-Sphere-StereographicProjection
An interactive Stereographic Projection of 4-dimensional sphere 3-sphere based on OpenGL

4维球体（3维球面）的球极投影程序。

## Files 文件
- S3GL01:<br>
Simple, incomplete version.<br>
预览版本。
- S3GLCV01:<br>
A complete version using 4D rotation matrix.<br>
使用了旋转矩阵的版本。
-S3GLCVLR01:<br>
3D side by side version. OpenGL part of codes are in S3GLCV01 folder.<br>
可切换左右眼3D模式。GL部分代码在S3GLCV01文件夹内。

## Control 控制

W-S, A-D, Q-E, 1-2, 3-4, 5-6: 4D rotation 四维旋转

Backspace: Reset 4D rotation 还原四维旋转

Z, X, C: Show/Hide meridians, hypermeridians and parallels 显示、隐藏各组经纬线

F-R: Change distance of viewpoint 调整视点距离

T-G: Change view angle 调整视角大小

V-B: Move 4D projection point, from Stereographic Projection to Direct Projection. Press P to reset to Stereographic Projection. 调整四维投影点距离，最小为球极投影，最大为正投影。按P键重置。

J-K: Change divsional angle 调整分割角，即各组经纬线内的角度

N-M: Change multiplier (A bigger multiplier makes the circles rounder) 调整乘数因子使多边形更接近圆

Comma-Period: Change thickness 调整粗细

Square Brackets: Adjust Pupil Distance in 3D mode 调整3D模式的瞳距

Slash or Question Mark: Enable, disable 3D mode 3D模式开关

## Preview 预览
