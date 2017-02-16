-- define SSID credentials
SSID = "ScreamBananaForPassword"
SSID_PASSWORD = "dingdong"

-- define mongoDB API key
mongoAPI_key = "265NHXlP3tObb374O6Sn9D4TkcqJEy_0"

-- mongoDB REST URLs
mongo_base_path = "https://api.mlab.com/api/1"

-- Relay IP
relay_ip = "http://52.38.18.190"
relay_test = "/test"
relay_insert = "/api/db/insert"
relay_retrieve = "/api/db/get"
relay_call = "/api/call"
relay_achieve = "/api/db/insert"
relay_get = "/api/db/get"


-- configure ESP as a station
wifi.setmode(wifi.STATION)
wifi.sta.config(SSID,SSID_PASSWORD)
wifi.sta.autoconnect(1)
gpio.mode(3, gpio.OUTPUT)
gpio.write(3, gpio.HIGH)

-- pause for connection to take place - adjust time delay if necessary or repeat until connection made
print("Waiting to establish wifi...")
tmr.delay(5000000) -- wait 1,000,000 us = 1 second
status = wifi.sta.status()
print(status)

count = 0
while (status ~= 5 and count <= 5)
do
  tmr.delay(3000000)
  print("Attempting to reconnect... "..count)
  wifi.setmode(wifi.STATION)
  wifi.sta.config(SSID,SSID_PASSWORD)
  wifi.sta.autoconnect(1)
  status = wifi.sta.status()
  count = count + 1
end

if (count <= 5) then
  print("Connected Successfully")
  gpio.write(3, gpio.LOW)
else
  print("Could not find connection")
  gpio.write(3, gpio.HIGH)
end

-- This function registers a function to echo back any response from the server, to our DE1/NIOS system
-- or hyper-terminal (depending on what the dongle is connected to)
function display(sck,response)
     print(response)
end


--
-- Insert a row specifically modeled to represent session statistics.
--
function insertDB(id, start_time, time_elapsed, state_latitude, start_longitude, end_latitude, end_longitude, total_distance, speed)

  -- Check wifi status before attempting the POST.
  status = wifi.sta.status()
  if (status ~= 5) then
    print("Wifi not setup yet. Status:"..status.." Aborting...@")
    return;
  end

  sampleTable = genTable(id, start_time, time_elapsed, state_latitude, start_longitude, end_latitude, end_longitude, total_distance, speed)
  encodedTable = cjson.encode(sampleTable)
  http.post(relay_ip..relay_insert, 'Content-Type: application/json\r\n', encodedTable, function(code,data)
    if (code < 0) then
      print("HTTP request failed.@")
    else
      print(code, data)
      print("@")
    end
  end)
end


--
--  Call specified number via Twilio API. number must be registered to our Twilio account.
--
function twilioCall(numberToCall)

  -- Check wifi status before attempting the POST.
  status = wifi.sta.status()
  if (status ~= 5) then
    print("Wifi not setup yet. Status:"..status.." Aborting...@")
    return;
  end

  table = {}
  table["to"] = numberToCall
  encodedTable = cjson.encode(table);
  http.post(relay_ip..relay_call, 'Content-Type: application/json\r\n', encodedTable, function(code,data)
    if (code < 0) then
      print("HTTP request failed.@")
    else
      print(code, data)
      print("@")
    end
  end)
end

--
-- Insert a row specifically modeled to hold information regarding achievement states.
--
function InsertAchieve(id, dist1, dist2, ses1, ses2, speed1, speed2, numSessions, achieve_radius)

  -- Check wifi status before attempting the POST.
  status = wifi.sta.status()
  if (status ~= 5) then
    print("Wifi not setup yet. Status:"..status.." Aborting...@")
    return;
  end

  table = {}
  table["_id"] = id
  table["distance1"] = dist1
  table["distance2"] = dist2
  table["session1"] = ses1
  table["session2"] = ses2
  table["speed1"] = speed1
  table["speed2"] = speed2
  table["numSessions"] = numSessions
  table["achievementRadius"] = achieve_radius
  encodedTable = cjson.encode(table);

  http.post(relay_ip..relay_achieve, 'Content-Type: application/json\r\n', encodedTable, function(code,data)
    if (code < 0) then
      print("HTTP request failed.@")
    else
      print(code, data)
      print("@")
    end
  end)
end


--
-- Update the previous sessions counter in the DB.
--
function getPrevSessionCount()

  -- Check wifi status before attempting the POST.
  status = wifi.sta.status()
  if (status ~= 5) then
    print("Wifi not setup yet. Status:"..status.." Aborting...@")
    return;
  end

  table = {}
  table["id"] = "sessionCount"
  encodedTable = cjson.encode(table)

  http.post(relay_ip..relay_get, 'Content-Type: application/json\r\n', encodedTable, function(code,data)
    if (code < 0) then
      print("HTTP request failed.@")
    else
      print(code, data)
      print("@")
    end
  end)
end

--
-- Update the previous sessions counter in the DB.
--
function updatePrevSessionCount(count)

  -- Check wifi status before attempting the POST.
  status = wifi.sta.status()
  if (status ~= 5) then
    print("Wifi not setup yet. Status:"..status.." Aborting...@")
    return;
  end

  table = {}
  table["_id"] = "sessionCount"
  table["count"] = count
  encodedTable = cjson.encode(table)

  http.post(relay_ip..relay_insert, 'Content-Type: application/json\r\n', encodedTable, function(code,data)
    if (code < 0) then
      print("HTTP request failed.@")
    else
      print(code, data)
      print("@")
    end
  end)
end


--
-- Get a row from the non-relational DB. Specify the ID of the row.
--
function getID(id)

  -- Check wifi status before attempting the POST.
  status = wifi.sta.status()
  if (status ~= 5) then
    print("Wifi not setup yet. Status:"..status.." Aborting...@")
    return;
  end

  table = {}
  table["id"] = id
  encodedTable = cjson.encode(table)
  http.post(relay_ip..relay_get, 'Content-Type: application/json\r\n', encodedTable, function(code,data)
    if (code < 0) then
      print("HTTP request failed.@")
    else
      print(code, data)
      print("@")
    end
  end)
end


--
-- Helper function to format a table for a Previous Fitness Session insert.
--
function genTable(id, start_time, time_elapsed, start_latitude, start_longitude, end_latitude, end_longitude, total_distance, speed)
  table = {}
  table["_id"] = id
  table["start_time"] = start_time
  table["end_time"] = time_elapsed
  table["start_lat"] = start_latitude
  table["start_long"] = start_longitude
  table["end_lat"] = end_latitude
  table["end_long"] = end_longitude
  table["total_distance"] = total_distance
  table["speed"] = speed
  return table
end
