! Created by  on 20. 10. 22..

module Perceptron_mod
    use Constants
    implicit none

    type perceptron
        integer :: dim
        real(kd), allocatable :: w(:)
    contains
        procedure :: init
        procedure, pass :: predict
        procedure, pass :: loss
        procedure, pass, private :: pfit
        procedure, pass :: fit
        final :: destroy
    end type perceptron

contains
    subroutine destroy(this)
        type(perceptron), intent(inout) :: this
        deallocate(this%w)
    end subroutine destroy

    subroutine init(this, n)
        class(perceptron), intent(inout) :: this
        integer, intent(in) :: n
        this%dim = n
        allocate(this%w(n + 1))
        call RANDOM_NUMBER(this%w)
    end subroutine init

    real(kd) function predict(self, xx)
        ! x is of dimension dim, but w is dim+1
        class(perceptron), intent(in) :: self
        real(kd), intent(in) :: xx(:)
        real(kd) :: x(size(xx) + 1)
        !! Init
        x(1) = 1
        x(2:) = xx
        predict = dot_product(x, self%w)
    end function predict

    real(kd) function loss(self, x, y)
        class(perceptron), intent(in) :: self
        real(kd), intent(in) :: x(:, :)
        integer, intent(in) :: y(:) ! y should be -1 or +1
        !local variables.
        integer :: i
        real(kd) :: total
        total = size(y)
        ! Proceeding
        loss = sum([(1, i = 1, size(y))]&
                , mask = [(self%predict(x(i, :)) * y(i)<0, i = 1, size(y))])&
                / total
    end function loss

    integer function pfit(self, x, y)
        class(perceptron), intent(inout) :: self
        real(kd), intent(in) :: x(:, :)
        integer, intent(in) :: y(:)
        ! Local Data
        integer :: iteration = 0, i
        ! Proceeding
        do while(self%loss(x, y)/=0)
            do i = 1, size(y)
                if(self%predict(x(i, :)) * y(i)<0) then
                    self%w = self%w + y(i) * [1._kd, x(i, :)]
                    iteration = iteration + 1
                end if
            end do
        end do
        pfit = iteration
    end function pfit

    subroutine fit(self, x, y, iter, loss)
        class(perceptron), intent(inout) :: self
        real(kd), intent(in) :: x(:, :)
        integer, intent(in) :: y(:)
        integer, intent(out) :: iter
        real(kd), intent(out) :: loss
        ! Return informations
        iter = self%pfit(x, y)
        loss = self%loss(x, y)

    end subroutine fit

end module Perceptron_mod