#!/bin/bash

set -e

function mx_kk_20130801_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u 10.10.121.100:/home/svn/amlogic_jb_mr1_mirror/jellybean/platform/manifest.git -b sdmc_nbox --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	repo sync -j4
	repo forall -c git checkout -b sdmc_nbox_130801 svn_org/sdmc_nbox_130801
	cd external
	git clone 10.10.121.100:/home/svn/amlogic_jb_mr1_mirror/jellybean/platform/external/sdmc-libs.git
	cd sdmc-libs
	git checkout -b sdmc_nbox_130801 origin/sdmc_nbox_130801
	cd ../../
	echo -e "\ndownload finished\n"
}

function mx_kk_20140428_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u 10.10.121.100:/home/svn/amlogic_jb_mr1_mirror/jellybean/platform/manifest.git -b sdmc_nbox_140428 --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	repo sync -j4
	repo forall -c git checkout -b sdmc_nbox_140428	svn_org/sdmc_nbox_140428
	cd external
	git clone 10.10.121.100:/home/svn/amlogic_jb_mr1_mirror/jellybean/platform/external/sdmc-libs.git
	cd sdmc-libs
	git checkout -b sdmc_nbox_140428 origin/sdmc_nbox_140428
	cd ../../
	echo -e "\ndownload finished\n"
}

function m8_kk_20150313_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u 10.10.121.100:/home/svn/amlogic_kk_git_mirror/kitkat/platform/manifest.git -b sdmc_m8_20150313 --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	repo sync -j4
	repo forall -c git checkout -b sdmc_m8_20150313_patch svn_org/sdmc_m8_20150313_patch
	mkdir -p vendor/sdmc
	cd vendor/sdmc
	git clone 10.10.121.100:/home/svn/amlogic_jb_mr1_mirror/jellybean/platform/external/sdmc-libs.git
	cd sdmc-libs
	git checkout -b sdmc_s805_20141114_patch origin/sdmc_s805_20141114_patch
	cd ../../../
	echo -e "\ndownload finished\n"
}

function m8_kk_20150414_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u 10.10.121.100:/home/svn/amlogic_kk_git_mirror/kitkat/platform/manifest.git -b sdmc_m8_20150414_patch --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	repo sync -j4
	repo forall -c git checkout -b sdmc_m8_20150414_patch svn_org/sdmc_m8_20150414_patch
	echo -e "\ndownload finished\n"
}

function m8_kk_20150612_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u 10.10.121.100:/home/svn/amlogic_kk_git_mirror/kitkat/platform/manifest.git -b sdmc_m8_20150612 --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	repo sync -j4
	repo forall -c git checkout -b sdmc_m8_20150612 svn_org/sdmc_m8_20150612
	echo -e "\ndownload finished\n"
}

function m8_l_20150514_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u 10.10.121.100:/home/svn/amlogic_kk_git_mirror/kitkat/platform/manifest.git -b sdmc_m8_5.0_20150514 --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	repo sync -j4
	repo forall -c git checkout -b sdmc_m8_lollipop_20150514 svn_org/sdmc_m8_lollipop_20150514
	echo -e "\ndownload finished\n"
}

function s805_buildrootSLC256_sdk()
{
	echo -e "\ndownload begin\n"
	git clone svn@10.10.61.22:/home/svn/amlogic_s805_linux_git_mirror/  -b	kk-amlogic_SLC256
	echo -e "\ndownload finished\n"
}

function s905_l_20150108_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u ssh://amlogic_l_group@10.10.61.22/home/svn/amlogic_l_gx_git_mirror/l-amlogic-gx/platform/manifest.git -b l-amlogic-gx --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	cd .repo/manifests
	cp openlinux_l-amlogic_20151031_patch_0108.xml default.xml
	sed -i "s/ssh:\/\/git@openlinux.amlogic.com/ssh:\/\/amlogic_l_group@10.10.61.22\/home\/svn\/amlogic_l_gx_git_mirror/" default.xml
	cd ../../
	repo sync -j4
	cd vendor/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/playready.git -b l-amlogic
	cd amlogic/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/tdk.git -b tdk-v1.2
	cd ../../
	echo -e "\ndownload finished\n"
}

function s905_l_20150401_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u ssh://amlogic_l_group@10.10.61.22/home/svn/amlogic_l_gx_git_mirror/l-amlogic-gx/platform/manifest.git -b l-amlogic-gx --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	cd .repo/manifests
	cp openlinux_l-amlogic_20151031_patch_0401.xml default.xml
	sed -i "s/ssh:\/\/git@openlinux.amlogic.com/ssh:\/\/amlogic_l_group@10.10.61.22\/home\/svn\/amlogic_l_gx_git_mirror/" default.xml
	cd ../../
	repo sync -j4
	cd vendor/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/playready.git -b l-amlogic
	cd amlogic/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/tdk.git -b tdk-v1.2
	cd ../../
	echo -e "\ndownload finished\n"
}

function s912_m_20160907_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u ssh://amlogic_l_group@10.10.61.22/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/platform/manifest.git -b m-amlogic-openlinux-20160907 --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	cd .repo/manifests
	cp openlinux_m-amlogic_20160907.xml default.xml
	sed -i "s/remote fetch=\"..\/../remote fetch=\"ssh:\/\/amlogic_l_group@10.10.61.22\/home\/svn\/amlogic_m_gxl_git_mirror/" default.xml
	cd ../../
	repo sync -j4
	cd vendor/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/playready.git -b m-amlogic
	cd amlogic/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/tdk.git -b tdk-v1.5
	cd ../../
	echo -e "\ndownload finished\n"
}

function s905x_m_20160907_sdk()
{
	s912_m_20160907_sdk
}

function s905d_20160907_sdk()
{
	s912_m_20160907_sdk
}

function s905x_m_20160907_vmx_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u ssh://amlogic_l_group@10.10.61.22/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/platform/manifest.git -b m-amlogic-openlinux-20160907 --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	cd .repo/manifests
	cp openlinux_m-amlogic_vmx.xml default.xml
	sed -i "s/remote fetch=\"..\/../remote fetch=\"ssh:\/\/amlogic_l_group@10.10.61.22\/home\/svn\/amlogic_m_gxl_git_mirror/" default.xml
	cd ../../
	repo sync -j4
	cd vendor/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/playready.git -b m-amlogic
	cd amlogic/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/tdk.git -b tdk-v1.5
	cd ../../
	echo -e "\ndownload finished\n"
}

function his3796MV100_kk_v63_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u hisilicon_group@10.10.61.22:/home/svn/hisilicon_kk_git_mirror/manifest.git -b his_3796_v58 --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	repo sync -j4
	repo forall -c git checkout -b his_v63_org 	org/his_v63_org
	echo -e "\ndownload finished\n"
}

function his3796MV100_kk_v64_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u hisilicon_group@10.10.61.22:/home/svn/hisilicon_kk_git_mirror/manifest.git -b his_3796_v58 --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	repo sync -j4
	repo forall -c git checkout -b his_v64_org 	org/his_v64_org
	echo -e "\ndownload finished\n"
}

function his3796MV100_kk_v65_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u hisilicon_group@10.10.61.22:/home/svn/hisilicon_kk_git_mirror/manifest.git -b his_3796_v58 --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	repo sync -j4
	repo forall -c git checkout -b his_v65_org 	org/his_v65_org
	echo -e "\ndownload finished\n"
}

function his3796MV100_l_v20_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u hisilicon_group@10.10.61.22:/home/svn/hisilicon_l_kk_git_mirror/manifest.git -b his_l_v20 --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	repo sync -j4
	repo forall -c git checkout -b his_l_v20_org org/his_l_v20_org
	echo -e "\ndownload finished\n"
}

function s912_n_20161230_sdk()
{
    echo -e "\ndownload begin\n"
    repo init -u ssh://amlogic_l_group@10.10.61.22/home/svn/amlogic_n_gx_git_mirror/n-amlogic/platform/manifest.git -b n-amlogic --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	cd .repo/manifests
	cp n-amlogic_openlinux-20161230.xml default.xml
	sed -i "s/remote fetch=\"..\/../remote fetch=\"ssh:\/\/amlogic_l_group@10.10.61.22\/home\/svn\/amlogic_n_gx_git_mirror/" default.xml
	cd ../../
	repo sync -j4
	cd vendor/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/playready.git -b n-amlogic-3.x
	cd amlogic/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/tdk.git -b tdk-v2.0
	cd ../../
	echo -e "\ndownload finished\n"
}

function s905x_n_20161230_sdk()
{
    s912_n_20161230_sdk
}

function s905d_n_20161230_sdk()
{
    s912_n_20161230_sdk
}

function s912_n_20170222_sdk()
{
    echo -e "\ndownload begin\n"
    repo init -u ssh://amlogic_l_group@10.10.61.22/home/svn/amlogic_n_gx_git_mirror/n-amlogic/platform/manifest.git -b n-amlogic --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	cd .repo/manifests
	cp n-amlogic_openlinux-20170222-ott.xml default.xml
	sed -i "s/remote fetch=\"..\/../remote fetch=\"ssh:\/\/amlogic_l_group@10.10.61.22\/home\/svn\/amlogic_n_gx_git_mirror/" default.xml
	cd ../../
	repo sync -j4
	cd vendor/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/playready.git -b n-amlogic-3.x
	cd amlogic/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/tdk.git -b tdk-v2.0
	cd ../../
	echo -e "\ndownload finished\n"
}

function s905x_n_20170222_sdk()
{
    s912_n_20170222_sdk
}

function s905d_n_20170222_sdk()
{
    s912_n_20170222_sdk
}

function s912_n_20170321_sdk()
{
    echo -e "\ndownload begin\n"
    repo init -u ssh://amlogic_l_group@10.10.61.22/home/svn/amlogic_n_gx_git_mirror/n-amlogic/platform/manifest.git -b n-amlogic --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	cd .repo/manifests
	cp n-amlogic_openlinux-20170321.xml default.xml
	sed -i "s/remote fetch=\"..\/../remote fetch=\"ssh:\/\/amlogic_l_group@10.10.61.22\/home\/svn\/amlogic_n_gx_git_mirror/" default.xml
	cd ../../
	repo sync -j4
	cd vendor/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/playready.git -b n-amlogic-3.x
	cd amlogic/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/tdk.git -b tdk-v2.0
	cd ../../
	echo -e "\ndownload finished\n"
}

function s905x_n_20170321_sdk()
{
    s912_n_20170321_sdk
}

function s905d_n_20170222_sdk()
{
    s912_n_20170321_sdk
}

function s912_n_20170425_sdk()
{
    echo -e "\ndownload begin\n"
    repo init -u ssh://amlogic_l_group@10.10.61.22/home/svn/amlogic_n_gx_git_mirror/n-amlogic/platform/manifest.git -b n-amlogic --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	cd .repo/manifests
	cp n-amlogic_openlinux-20170425.xml default.xml
	sed -i "s/remote fetch=\"..\/../remote fetch=\"ssh:\/\/amlogic_l_group@10.10.61.22\/home\/svn\/amlogic_n_gx_git_mirror/" default.xml
	cd ../../
	repo sync -j4
	cd vendor/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/playready.git -b n-amlogic-3.x
	cd amlogic/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/tdk.git -b tdk-v2.0
	cd ../../
	echo -e "\ndownload finished\n"
}

function s905x_n_20170425_sdk()
{
    s912_n_20170425_sdk
}

function s905d_n_20170425_sdk()
{
    s912_n_20170425_sdk
}

function his3798MV200_n_v23_sdk()
{
	echo -e "\ndownload begin\n"
	repo init -u hisilicon_group@10.10.61.22:/home/svn/hisilicon_n_git_mirror/manifest.git -b master --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	repo sync -j4
	repo forall -c git checkout -b his_n_v23_org org/his_n_v23_org
	echo -e "\ndownload finished\n"
}

function s912_n_20170619_sdk()
{
    echo -e "\ndownload begin\n"
    repo init -u ssh://amlogic_l_group@10.10.61.22/home/svn/amlogic_n_gx_git_mirror/n-amlogic/platform/manifest.git -b n-amlogic --repo-url=$USER@10.10.121.100:/usr/tools/repo.git
	cd .repo/manifests
	cp n-amlogic_openlinux-20170619.xml default.xml
	sed -i "s/remote fetch=\"..\/../remote fetch=\"ssh:\/\/amlogic_l_group@10.10.61.22\/home\/svn\/amlogic_n_gx_git_mirror/" default.xml
	cd ../../
	repo sync -j4
	cd vendor/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/playready.git -b n-amlogic-3.x
	cd amlogic/
	git clone amlogic_l_group@10.10.61.22:/home/svn/amlogic_m_gxl_git_mirror/m-amlogic/tdk.git -b tdk-v2.0
	cd ../../
	echo -e "\ndownload finished\n"
}

function s905x_n_20170619_sdk()
{
    s912_n_20170619_sdk
}

function s905d_n_20170619_sdk()
{
    s912_n_20170619_sdk
}
function mkdir_sdk()
{
	sdk_dir=$1

    while [ -d "$sdk_dir" ]
	do
	    echo  "$sdk_dir has existed, you can enter a custom directory ["eg:normal"]"
        export TARGET_SDK_DIR_TYPE=
		export ANSWER=
        local ANSWER
        while [ -z $TARGET_SDK_DIR_TYPE ]
        do
            read ANSWER
            if [ -n "$ANSWER" ] ; then
			    sdk_dir=$1_$ANSWER
                break
            fi
        done
    done

	mkdir $sdk_dir
    echo "sdk will download in $sdk_dir directory"
    cd $sdk_dir
}

function choose_info()
{
	echo
	echo "You're downloding a soc sdk"
	echo
	echo "Lunch menu... pick a combo:"
	echo "          1. mx 20130801 android 4.2 sdk"
	echo "          2. mx 20140428 android 4.2 sdk"
	echo "          3. m8 20150313 android 4.4 sdk"
	echo "          4. m8 20150414 android 4.4 sdk"
	echo "          5. m8 20150612 android 4.4 sdk"
	echo "          6. m8 20150514 android 5.1 sdk"
	echo "          7. s805 SLC256 buildroot sdk"
	echo "          8. s905 20150108 android 5.1 sdk"
	echo "          9. s905 20150401 android 5.1 sdk"
	echo "          10. s912 20160907 android 6.0 sdk"
	echo "          11. s905x 20160907 android 6.0 sdk"
	echo "          12. s905d 20160907 android 6.0 sdk"
	echo "          13. his3796MV100 v63 android 4.4 sdk"
	echo "          14. his3796MV100 v64 android 4.4 sdk"
	echo "          15. his3796MV100 v65 android 4.4 sdk"
	echo "          16. his3796MV100 v20 android 5.1 sdk"
	echo "          17. s905x 20160907 android 6.0 verimatrix sdk"
	echo "          18. s912 20161230 android 7.0 sdk"
	echo "          19. s905x 20161230 android 7.0 sdk"
	echo "          20. s905d 20161230 android 7.0 sdk"
	echo "          21. s912 20170222 android 7.1 sdk"
	echo "          22. s905x 20170222 android 7.1 sdk"
	echo "          23. s905d 20170222 android 7.1 sdk"
	echo "          24. s912 20170321 android 7.1 sdk"
	echo "          25. s905x 20170321 android 7.1 sdk"
	echo "          26. s905d 20170321 android 7.1 sdk"
	echo "          27. s912 20170425 android 7.1 sdk"
	echo "          28. s905x 20170425 android 7.1 sdk"
	echo "          29. s905d 20170425 android 7.1 sdk"
	echo "          30. his3798MV200 v23 android 7.0 sdk"
	echo "          31. s912 20170619 android 7.1 sdk"
	echo "          32. s905x 20170619 android 7.1 sdk"
	echo "          33. s905d 20170619 android 7.1 sdk"
	echo
}

function choose_type()
{
	choose_info
    export TARGET_BUILD_TYPE=
    local ANSWER
    while [ -z $TARGET_BUILD_TYPE ]
    do
        echo -n "Which SDK would you like to download? ["$DEFAULT_NUM"] "
        if [ -z "$1" ] ; then
            read ANSWER
        else
            echo $1
            ANSWER=$1
        fi
        case $ANSWER in
        "")
            echo "please select a sdk to download!"
            ;;
        1)
            echo "downloding mx 20130801 android 4.2 sdk"
			SDK_DIR=mx_kk_20130801_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
            ;;
        2)
            echo "downloding mx 20140428 android 4.2 sdk"
			SDK_DIR=mx_kk_20140428_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
            ;;
        3)
            echo "downloding m8 20150313 android 4.4 sdk"
			SDK_DIR=m8_kk_20150313_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
            ;;
        4)
            echo "downloding m8 20150414 android 4.4 sdk"
			SDK_DIR=m8_kk_20150414_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
            ;;
        5)
            echo "downloding m8 20150612 android 4.4 sdk"
			SDK_DIR=m8_kk_20150612_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
            ;;
        6)
            echo "downloding m8 20150514 android 5.1 sdk"
			SDK_DIR=m8_l_20150514_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
            ;;
        7)
            echo "downloding s805 SLC256 buildroot sdk"
			SDK_DIR=s805_buildrootSLC256_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
            ;;
        8)
            echo "downloding s905 20150108 android 5.1 sdk"
			SDK_DIR=s905_l_20150108_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
            ;;
        9)
            echo "downloding s905 20150401 android 5.1 sdk"
			SDK_DIR=s905_l_20150401_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
            ;;
        10)
            echo "downloding s912 20160907 android 6.0 sdk"
			SDK_DIR=s912_m_20160907_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        11)
            echo "downloding s905x 20160907 android 6.0 sdk"
			SDK_DIR=s905x_m_20160907_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        12)
            echo "downloding s905d 20160907 android 6.0 sdk"
			SDK_DIR=s905d_m_20160907_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        13)
            echo "downloding his3796MV100 v63 android 4.4 sdk"
			SDK_DIR=his3796MV100_kk_v63_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        14)
            echo "downloding his3796MV100 v64 android 4.4 sdk"
			SDK_DIR=his3796MV100_kk_v64_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        15)
            echo "downloding his3796MV100 v65 android 4.4 sdk"
			SDK_DIR=his3796MV100_kk_v65_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        16)
            echo "downloding his3796MV100 v20 android 5.1 sdk"
			SDK_DIR=his3796MV100_l_v20_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        17)
            echo "downloding s905x 20160907 android 6.0 verimatrix sdk"
			SDK_DIR=s905x_m_20160907_vmx_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        18)
            echo "downloding s912 20161230 android 7.0 sdk"
			SDK_DIR=s912_n_20161230_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        19)
            echo "downloding s905x 20161230 android 7.0 sdk"
			SDK_DIR=s905x_n_20161230_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        20)
            echo "downloding s905d 20161230 android 7.0 sdk"
			SDK_DIR=s905d_n_20161230_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        21)
            echo "downloding s912 20170222 android 7.1 sdk"
			SDK_DIR=s912_n_20170222_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        22)
            echo "downloding s905x 20170222 android 7.1 sdk"
			SDK_DIR=s905x_n_20170222_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        23)
            echo "downloding s905d 20170222 android 7.1 sdk"
			SDK_DIR=s905d_n_20170222_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        24)
            echo "downloding s912 20170321 android 7.1 sdk"
			SDK_DIR=s912_n_20170321_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        25)
            echo "downloding s905x 20170321 android 7.1 sdk"
			SDK_DIR=s905x_n_20170321_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        26)
            echo "downloding s905d 20170321 android 7.1 sdk"
			SDK_DIR=s905d_n_20170321_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        27)
            echo "downloding s912 20170425 android 7.1 sdk"
			SDK_DIR=s912_n_20170425_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        28)
            echo "downloding s905x 20170425 android 7.1 sdk"
			SDK_DIR=s905x_n_20170425_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        29)
            echo "downloding s905d 20170425 android 7.1 sdk"
			SDK_DIR=s905d_n_20170425_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        30)
            echo "downloding his3798MV200 v23 android 7.0 sdk"
			SDK_DIR=his3798MV200_n_v23_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        31)
            echo "downloding s912 20170619 android 7.1 sdk"
			SDK_DIR=s912_n_20170619_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        32)
            echo "downloding s905x 20170619 android 7.1 sdk"
			SDK_DIR=s905x_n_20170619_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        33)
            echo "downloding s905d 20170619 android 7.1 sdk"
			SDK_DIR=s905d_n_20170619_sdk
			mkdir_sdk $SDK_DIR
			$SDK_DIR
			;;
        *)
            echo
            echo "I didn't understand your response.  Please try again."
            echo
            ;;
        esac
        if [ -n "$SDK_DIR" ] ; then
            break
        fi
    done
}

    choose_type
