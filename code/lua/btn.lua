btn_a = 2
btn_b = 1

led_r_pin = 5 -- GPIO 14

gpio.mode(btn_a, gpio.INT)
gpio.mode(btn_b, gpio.INT)

gpio.mode(led_r_pin, gpio.OUTPUT)

function on()
    gpio.write(led_r_pin, 0)
end

function off()
    gpio.write(led_r_pin, 1)
end

off()

gpio.trig(btn_a, "down", function (level)
    if level == gpio.LOW then
        print "A"
        on()
    end
end)

gpio.trig(btn_b, "down", function (level)
    if level == gpio.LOW then
        print "B"
        off()
    end
end)
