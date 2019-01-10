# Bazel (http://bazel.io/) BUILD file for ceres

licenses(["notice"])

COPTS = [
    "-std=c++11",
]
LINK_OPTS = [
]

genrule(
    name = "ceres-config",
    srcs = [
        "cmake",
        "include",
        "internal",
        "CMakeLists.txt",
    ],
    outs = [
        "include/ceres/internal/config.h",
    ],
    cmd = """
        TMPDIR=$$(mktemp -d) \
        && mkdir -p $(@D) \
        && cp -Lr $(SRCS) $$TMPDIR \
        && mkdir $$TMPDIR/build \
        && (cd $$TMPDIR/build && cmake .. -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DCXX11=ON -DCXSPARSE=OFF -DBUILD_TESTING=OFF -DBUILD_EXAMPLES=OFF) \
        && cp -rf $$TMPDIR/build/config/ceres/internal/config.h $(OUTS) \
        && rm -rf $$TMPDIR
    """,
    tools = [
    ]
)

cc_library(
    name = "ceres",
    srcs = glob([
        "internal/ceres/array_utils.cc",
        "internal/ceres/blas.cc",
        "internal/ceres/block_evaluate_preparer.cc",
        "internal/ceres/block_jacobi_preconditioner.cc",
        "internal/ceres/block_jacobian_writer.cc",
        "internal/ceres/block_random_access_dense_matrix.cc",
        "internal/ceres/block_random_access_diagonal_matrix.cc",
        "internal/ceres/block_random_access_matrix.cc",
        "internal/ceres/block_random_access_sparse_matrix.cc",
        "internal/ceres/block_sparse_matrix.cc",
        "internal/ceres/block_structure.cc",
        "internal/ceres/c_api.cc",
        "internal/ceres/canonical_views_clustering.cc",
        "internal/ceres/cgnr_solver.cc",
        "internal/ceres/callbacks.cc",
        "internal/ceres/compressed_col_sparse_matrix_utils.cc",
        "internal/ceres/compressed_row_jacobian_writer.cc",
        "internal/ceres/compressed_row_sparse_matrix.cc",
        "internal/ceres/conditioned_cost_function.cc",
        "internal/ceres/conjugate_gradients_solver.cc",
        "internal/ceres/coordinate_descent_minimizer.cc",
        "internal/ceres/corrector.cc",
        "internal/ceres/covariance.cc",
        "internal/ceres/covariance_impl.cc",
        "internal/ceres/cxsparse.cc",
        "internal/ceres/dense_normal_cholesky_solver.cc",
        "internal/ceres/dense_qr_solver.cc",
        "internal/ceres/dense_sparse_matrix.cc",
        "internal/ceres/detect_structure.cc",
        "internal/ceres/dogleg_strategy.cc",
        "internal/ceres/dynamic_compressed_row_jacobian_writer.cc",
        "internal/ceres/dynamic_compressed_row_sparse_matrix.cc",
        "internal/ceres/dynamic_sparse_normal_cholesky_solver.cc",
        "internal/ceres/evaluator.cc",
        "internal/ceres/eigensparse.cc",
        "internal/ceres/file.cc",
        "internal/ceres/function_sample.cc",
        "internal/ceres/gradient_checker.cc",
        "internal/ceres/gradient_checking_cost_function.cc",
        "internal/ceres/gradient_problem.cc",
        "internal/ceres/gradient_problem_solver.cc",
        "internal/ceres/implicit_schur_complement.cc",
        "internal/ceres/inner_product_computer.cc",
        "internal/ceres/is_close.cc",
        "internal/ceres/iterative_schur_complement_solver.cc",
        "internal/ceres/levenberg_marquardt_strategy.cc",
        "internal/ceres/lapack.cc",
        "internal/ceres/line_search.cc",
        "internal/ceres/line_search_direction.cc",
        "internal/ceres/line_search_minimizer.cc",
        "internal/ceres/line_search_preprocessor.cc",
        "internal/ceres/linear_least_squares_problems.cc",
        "internal/ceres/linear_operator.cc",
        "internal/ceres/linear_solver.cc",
        "internal/ceres/local_parameterization.cc",
        "internal/ceres/loss_function.cc",
        "internal/ceres/low_rank_inverse_hessian.cc",
        "internal/ceres/minimizer.cc",
        "internal/ceres/normal_prior.cc",
        "internal/ceres/parameter_block_ordering.cc",
        "internal/ceres/partitioned_matrix_view.cc",
        "internal/ceres/polynomial.cc",
        "internal/ceres/preconditioner.cc",
        "internal/ceres/preprocessor.cc",
        "internal/ceres/problem.cc",
        "internal/ceres/problem_impl.cc",
        "internal/ceres/program.cc",
        "internal/ceres/reorder_program.cc",
        "internal/ceres/residual_block.cc",
        "internal/ceres/residual_block_utils.cc",
        "internal/ceres/schur_complement_solver.cc",
        "internal/ceres/schur_eliminator.cc",
        "internal/ceres/schur_jacobi_preconditioner.cc",
        "internal/ceres/schur_templates.cc",
        "internal/ceres/scratch_evaluate_preparer.cc",
        "internal/ceres/single_linkage_clustering.cc",
        "internal/ceres/solver.cc",
        "internal/ceres/solver_utils.cc",
        "internal/ceres/sparse_matrix.cc",
        "internal/ceres/sparse_cholesky.cc",
        "internal/ceres/sparse_normal_cholesky_solver.cc",
        "internal/ceres/split.cc",
        "internal/ceres/stringprintf.cc",
        "internal/ceres/suitesparse.cc",
        "internal/ceres/triplet_sparse_matrix.cc",
        "internal/ceres/trust_region_preprocessor.cc",
        "internal/ceres/trust_region_minimizer.cc",
        "internal/ceres/trust_region_step_evaluator.cc",
        "internal/ceres/trust_region_strategy.cc",
        "internal/ceres/types.cc",
        "internal/ceres/visibility.cc",
        "internal/ceres/visibility_based_preconditioner.cc",
        "internal/ceres/wall_time.cc",
        "internal/ceres/generated/*.cc",
    ]),
    hdrs = [
        "include/ceres/internal/config.h",
    ] + glob([
        "internal/ceres/*.h",
        "include/ceres/*.h",
        "include/ceres/internal/*.h",
    ]),
    includes = [
        "include",
        "internal",
        "internal/ceres",
    ],
    defines = [
        "EIGEN_MPL2_ONLY",
        "CERES_SUITESPARSE_VERSION=\\\"4.5.0\\\"",
    ],
    copts = COPTS + [
        "-fPIC",
        "-fopenmp",
    ],
    linkopts = LINK_OPTS + [
        "-pthread",
    ],
    linkstatic = True,
    deps = [
        "@com_github_google_glog//:glog",
        "@com_github_eigen_eigen//:eigen",
        "@suite_sparse//:static_cholmod",
    ],
    visibility = ["//visibility:public"],
)
