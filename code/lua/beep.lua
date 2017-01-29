
pin = 8

pwm.setup(pin, 1000, 512)
pwm.setclock(pin, 800)

pwm.start(pin)


for i = 100,1000,100 do
    print(i)

    pwm.setclock(pin, i)
    
    tmr.delay(500000)
    tmr.wdclr()
end

pwm.stop(pin)


