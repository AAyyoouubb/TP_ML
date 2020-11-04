! Created by  on 20. 10. 22..

module delta_rule_mod
    use Constants
    implicit none

    type delta_rule
        integer :: dim
        real(kd), allocatable :: w(:)
    contains
        procedure :: init
        procedure, pass :: predict
        procedure, pass :: loss
        procedure, pass :: fit
        final :: destroy
    end type delta_rule

contains
    subroutine destroy(this)
        type(delta_rule), intent(inout) :: this
        deallocate(this%w)
    end subroutine destroy

    subroutine init(this, n)
        class(delta_rule), intent(inout) :: this
        integer, intent(in) :: n
        this%dim = n
        allocate(this%w(n + 1))
        call RANDOM_NUMBER(this%w)
    end subroutine init

    real(kd) function predict(self, xx)
        ! x is of dimension dim, but w is dim+1
        class(delta_rule), intent(in) :: self
        real(kd), intent(in) :: xx(:)
        real(kd) :: x(size(xx) + 1)
        !! Init
        x(1) = 1
        x(2:) = xx
        predict = dot_product(x, self%w)
    end function predict

    real(kd) function loss(self, x, y)
        class(delta_rule), intent(in) :: self
        real(kd), intent(in) :: x(:, :)
        integer, intent(in) :: y(:) ! y should be -1 or +1
        !local variables.
        integer :: i
        real(kd) :: total
        total = size(y)
        ! Proceeding
        loss = sum([((self%predict(x(i, :)) - y(i))**2, i = 1, size(y))]) / total
    end function loss

    subroutine fit(self, x, y, iter, loss)
        class(delta_rule), intent(inout) :: self
        real(kd), intent(in) :: x(:, :)
        integer, intent(in) :: y(:), iter
        real(kd), intent(out) :: loss
        ! Local Data
        integer :: iteration, i
        real(kd) :: tmp
        ! Proceeding
        do iteration = 1, iter
            do i = 1, size(y)
                tmp = y(i) - self%predict(x(i, :))
                if(tmp/=0) then
                    self%w = self%w + 2 * tmp * [1._kd, x(i, :)] / size(y)
                end if
            end do
            loss = self%loss(x, y)
            write(*, *)iteration, "  ", loss
        end do

    end subroutine fit

end module delta_rule_mod