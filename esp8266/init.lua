--自动连接
dofile('httpServer.lua')
label =''
temp_data = ' '
humi_data = ' '
meth_data = ' '
light_data = ' '



httpServer:use('/temp', function(req, res)
    res:send(temp_data)
end)

httpServer:use('/humi', function(req, res)
    res:send(humi_data)
end)

httpServer:use('/meth', function(req, res)
    res:send(meth_data)
end)

httpServer:use('/light', function(req, res)
    light_data = "light "..2*adc.read(0).." CD"
    res:send(light_data)
end)


httpServer:listen(80) 
--启动Server

uart.on("data", "\r",
  function(data)
    label = string.sub(data,1,4)
    print(label)
    if label == "temp" then
      temp_data = data
    end
    if label == "humi" then
      humi_data = data
    end
    if label == "meth" then
       meth_data = data
    end
    if data=="quit\r" then
      uart.on("data") -- unregister callback function
    end
end, 0)
