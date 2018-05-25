using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Draw : MonoBehaviour {

	[Range(2.0f,10.0f)]
	public float constN=1000.0f;

	int width=1024,height=1024;
	Texture2D tex;

	double scale=1.0f;//倍率

	double cl1X=-2.3-0.5,cl1Y=-2.3;//クリッピング始点

	double clWidth;//クリッピング幅
	double clHeight;//クリッピング高さ

	double dvgJdg = 5.0;//発散の判定値
	double dvgMaxtm=100;//発散の判定試行回数
	bool dvgFlag;//発散フラグ


	double jdgX,jdgY;//発散判定する座標

	double rfX,rfY;
	double rfXn,rfYn;

	int i,ix,iy;

	void Start () {
		tex = new Texture2D (width, height);
		Sprite sprite=Sprite.Create(
			texture : tex,
			rect : new Rect(0,0,width,height),
			pivot : new Vector2(0.5f,0.5f)
		);
		GetComponent<SpriteRenderer>().sprite=sprite;
	}

	Color col=new Color(0.0f,0.0f,0.0f);
	Color bg=new Color(1.0f,1.0f,1.0f);
	// Update is called once per frame
	void Update (){

		if (Input.GetKey (KeyCode.W))cl1Y += clWidth*0.1f;
		if (Input.GetKey (KeyCode.S))cl1Y -= clWidth*0.1f;
		if (Input.GetKey (KeyCode.A))cl1X -= clWidth*0.1f;
		if (Input.GetKey (KeyCode.D))cl1X+= clWidth*0.1f;


		if (Input.GetKey (KeyCode.E))scale += scale*0.2;
		if (Input.GetKey (KeyCode.R))scale -= scale*0.2;
		if (scale <= 0)scale = 0.2f;


		clWidth = 4.6/scale;
		clHeight = 4.6/scale;


		for (iy=0; iy < height; iy++) {
			for (ix=0; ix < width; ix++) {
				tex.SetPixel (ix, iy, bg);
			}
		}

		for (iy = 0; iy < height; iy++) {
			jdgY = cl1Y + clHeight * iy / height;
			for(ix = 0; ix < width; ix++){

				jdgX = cl1X + clWidth * ix / width;

				rfX = 0.0;rfY = 0.0;

				dvgFlag = false;
				for (i = 0; i < dvgMaxtm; i++) {

					rfXn = rfX * rfX - rfY * rfY + jdgX;
					if (dvgJdg < rfXn){
						dvgFlag = true;
						break;
					}

					rfYn=constN*rfX*rfY+jdgY;
					if (dvgJdg < rfYn) {
						dvgFlag = true;
						break;
					}
					rfX = rfXn;
					rfY = rfYn;
				}

				if (!dvgFlag){
					tex.SetPixel (ix, iy, col);
				}
			}
		}
		tex.Apply ();
	}
}
