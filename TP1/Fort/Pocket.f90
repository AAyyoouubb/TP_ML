! Created by  on 20. 10. 22..

module pocket_mod
    use Constants
    implicit none

    private
    public fitt

contains

    real(kd) function predict(w, xx)
        ! x is of dimension dim, but w is dim+1
        real(kd), intent(in) :: xx(:), w(:)
        real(kd) :: x(size(xx) + 1)
        !! Init
        x(1) = 1
        x(2:) = xx
        predict = dot_product(x, w)
    end function predict

    real(kd) function loss(w, x, y)
        real(kd), intent(in) :: x(:, :), w(:)
        integer, intent(in) :: y(:) ! y should be -1 or +1
        !local variables.
        integer :: i
        real(kd) :: total
        total = size(y)
        ! Proceeding
        loss = sum([(1, i = 1, size(y))]&
                , mask = [(predict(w, x(i, :)) * y(i)<0, i = 1, size(y))])&
                / total
    end function loss

    real(kd) function pfit(w, x, y, iter)
        real(kd), intent(in) :: x(:, :)
        real(kd), intent(inout) :: w(:)
        integer, intent(in) :: y(:), iter
        ! Local Data
        integer :: iteration, i
        real(kd) :: w_tmp(size(w))
        ! Proceeding
        do iteration = 1, iter
            this : do i = 1, size(y)
                if(predict(w, x(i, :)) * y(i)<0) then
                    w_tmp = w + y(i) * [1._kd, x(i, :)]
                    if (loss(w_tmp, x, y)<pfit) then
                        w = w_tmp
                        exit this
                    end if
                end if
            end do this
            pfit = loss(w, x, y)
            write(*, *) iteration, "  ", pfit
        end do
    end function pfit

    subroutine fitt(w, x, y, iter, loss)
        real(kd), intent(in) :: x(:, :)
        integer, intent(in) :: y(:)
        integer, intent(in) :: iter
        real(kd), intent(out) :: loss, w(:)
        ! Return informations
        call random_number(w)
        loss = pfit(w, x, y, iter)

    end subroutine fitt

end module pocket_mod