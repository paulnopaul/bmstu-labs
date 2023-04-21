package key

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"strings"
)

const DsKeyPath = "/.ds_app_conf"

type keyStruct struct {
	Key string `json:"key"`
}

func WriteKey() error {
	snum, err := getSystemProfilerInfo()
	if err != nil {
		return err
	}
	data := keyStruct{Key: snum}
	fileData, _ := json.MarshalIndent(data, "", " ")
	fullPath, err := os.UserHomeDir()
	if err != nil {
		return err
	}
	fullPath += DsKeyPath
	err = ioutil.WriteFile(fullPath, fileData, 0644)
	return err
}

func CheckKey() (bool, error) {
	fullPath, err := os.UserHomeDir()
	if err != nil {
		return false, err
	}
	fullPath += DsKeyPath
	jsonFile, err := os.Open(fullPath)
	if err != nil {
		return false, err
	}
	defer jsonFile.Close()
	res, err := ioutil.ReadAll(jsonFile)
	if err != nil {
		return false, err
	}
	resStruct := new(keyStruct)
	err = json.Unmarshal(res, resStruct)
	if err != nil || resStruct == nil {
		return false, err
	}
	snum, err := getSystemProfilerInfo()
	if err != nil {
		return false, err
	}
	return resStruct.Key == snum, nil
}

func getSystemProfilerInfo() (string, error) {
	var snum string
	out, err := exec.Command("/usr/sbin/ioreg", "-l").Output() // err ignored for brevity
	if err != nil {
		return "", err
	}
	for _, l := range strings.Split(string(out), "\n") {
		if strings.Contains(l, "IOPlatformSerialNumber") {
			s := strings.Split(l, " ")
			snum = s[len(s)-1]
			return strings.Trim(snum, "\""), nil
		}
	}
	return "", fmt.Errorf("no serial number provided")
}
