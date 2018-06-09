x1 =[ -1.1, 1.5, 2.6;
       3.1, 4.5, 5.2;
       4.1, 7.6, 1.2];
x2 =[  4.3, 3.5, 6.4;
       3.7, 8.1, 4.4;
       5.6, 5.3, 2.3];

H = get_homography_25pt(x1, x2);
H = mat2cell(H, 3, 3 * ones(1, size(H, 2) / 3));

for k = 1:length(H)
    H{k} / H{k}(end)
end