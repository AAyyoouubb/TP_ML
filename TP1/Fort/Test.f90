! Created by  on 20. 10. 23..

program Test

    use Perceptron_mod
    use delta_rule_mod
    use pocket_mod
    use Constants

    implicit none

    integer, parameter :: n = 400, d = 2
    integer :: i
    integer :: y(n) = [((-1)**i, i = 1, n)], iter ,iterr=3
    real(kd) :: x(n, d), los, w(d+1)
    type(perceptron) :: p

    !    x = transpose(reshape([(y(i) / 2.*log(i*1.), 0., i = 1, n)], [d,n]))
    x(:, 1) = [(y(i) / 2. * log(i * 1.), i = 1, n)]
    x(:, 2) = 2 * x(:, 1)

    call p%init(d)

    call p%fit(x, y, iter, los)
    write(*, *) iter, los
    write(*, *) p%w

    call fitt(w, x, y, iterr, los)
    write(*, *) iterr, los
    write(*, *) w

end program Test