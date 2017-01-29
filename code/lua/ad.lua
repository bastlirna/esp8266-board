-- in you init.lua:
if adc.force_init_mode(adc.INIT_ADC)
then
  node.restart()
  return -- don't bother continuing, the restart is scheduled
end

print(adc.read(0))

tmr.alarm(0, 500, tmr.ALARM_AUTO, function() print(adc.read(0)) end)
