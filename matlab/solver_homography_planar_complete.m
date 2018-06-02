function H = solver_homography_planar_complete(x1, x2)
%SOLVER_HOMOGRAPHY_PLANAR_COMPLETE Returns a homography compatible with the
% general planar motion model from 3.5 point correspondences.
%   The function is based on the work by Wadenback et al. (ICIP, 2016)
%   and requires a pre-compiled function solver_homography_planar.
%   Instructions for doing so is in the README-file of this repository.

nbr_pts = 3;
assert(size(x1, 1) == nbr_pts)
assert(size(x2, 1) == nbr_pts)

% Cast points to double
x1 = double(x1);
x2 = double(x2);

% Construct 2.5 pt DLT system
dlt = [];
for k = 1:nbr_pts
    tmp = kron(x1(:,k)', crossm(x2(:,k)));
    dlt = [dlt; tmp(1:2,:)];
end

% Throw away one equation
dlt = dlt(1:5, :);
basis = null(dlt);

% Sanity check
if numel(basis) ~= 9*4
    warning('The DLT system has an unexpected basis.');
    H = {eye(3)};
    return
end

% Find coefficients
sols = solver_homography_planar(basis(:));

% Discard complex-valued solutions
real_sols = sols(:, imag(sols(1, :)) == 0);
nbr_real_sols = size(real_sols, 2);

% Generate putative solutions
H = cell(nbr_real_sols, 1);
for j = 1:nbr_real_sols
    coeffs = [real_sols(:, j); 1];   % Append constant term
    H{j} = reshape(sum(repmat(coeffs', 9, 1) .* double(basis), 2), 3, 3);
end

function K = crossm(k)
% Cross-product matrix
if numel(k) ~= 3
   error('Incorrect size of input vector.') 
end
K = [0 -k(3) k(2); k(3) 0 -k(1); -k(2) k(1) 0];
