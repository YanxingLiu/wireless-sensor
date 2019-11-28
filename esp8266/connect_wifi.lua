wifi.setmode(wifi.STATION)
wifi.sta.autoconnect(1)
station_cfg={}
station_cfg.ssid="yat"
station_cfg.pwd="13579abc"
--station_cfg.ssid="vivo X9i"
--station_cfg.pwd="8910jqka"
station_cfg.save=true
wifi.sta.config(station_cfg)
