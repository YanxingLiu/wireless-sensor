srv = net.createServer(net.TCP)
label =''
temp_data = ' '
humi_data = ' '
meth_data = ' '
light_data = ' '
function receiver(sck, data)
  local response = {}

  -- if you're sending back HTML over HTTP you'll want something like this instead
  -- local response = {"HTTP/1.0 200 OK\sr\nServer: NodeMCU on ESP8266\r\nContent-Type: text/html\r\n\r\n"}
    
    light_data = adc.read(0)
  response[#response + 1] = temp_data.."\r"
  response[#response + 1] = humi_data.."\r"
  response[#response + 1] = meth_data.."\r"
  response[#response + 1] = "light "..light_data.."\r"
  -- sends and removes the first element from the 'response' table
  local function send(localSocket)
    if #response > 0 then
      localSocket:send(table.remove(response, 1))
    else
      localSocket:close()
      response = nil
    end
  end
  -- triggers the send() function again once the first chunk of data was sent
  sck:on("sent", send)

  send(sck)
end

srv:listen(80, function(conn)
  conn:on("receive", receiver)
end)
--uart.alt(0)
--uart.setup(0, 115200, 8, uart.PARITY_NONE, uart.STOPBITS_1, 0)
--print(uart.getconfig(0))
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
